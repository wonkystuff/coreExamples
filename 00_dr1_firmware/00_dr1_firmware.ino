/*
 *
 * dr1.a 'drone synth' code
 * Output 1 - Main audio;
 * Output 2 - Square-wave sub-oscillator
 *
 * Controls:
 *   Knob I   :: 'perturbation' (random switching of wavetables
 *   Knob II  :: wavetable select (Sine, Triangle, Square, Saw with intermediate positions being a blend)
 *   Knob III :: Main oscillator (Fundamental pitch)
 *   Knob IV  :: Secondary oscillator (enveloped by the main oscillator)
 *
 * 2018-2021  by John Tuffen for wonkystuff®
 *   https://wonkystuff.net/
 *   https://wonkystuff.github.io/arduino/
 *
 * This example code is in the public domain.
 */

 #include "wonkystuffCommon.h"

#include "dr1_defs.h"

const uint8_t     *waves[5];  // choice of wavetable
const uint8_t     *wave1;     // which wavetable will this oscillator use?
const uint8_t     *wave2;     // which wavetable will this oscillator use?
uint16_t          phase;      // The accumulated phase (distance through the wavetable)
uint16_t          pi;         // wavetable current phase increment (how much phase will increase per sample)
uint16_t          phase_sync; // The accumulated phase of the (virtual) sync oscillator (distance through the wavetable)
uint16_t          pi_sync;    // sync oscillator current phase increment (how much phase will increase per sample)

void
setup(void)
{

  wsInit();                 // general initialisation
  wsInitPWM();              // We're using PWM here
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!

  waves[0] = sine;
  waves[1] = triangle;
  waves[2] = sq;
  waves[3] = ramp;
  waves[4] = sine;

  pi = 1;
  pi_sync = 1;

}

void
loop(void)
{
  static uint8_t  adcNum=0;                // declared as static to limit variable scope
  static uint8_t  waveSelect;
  static uint8_t  perturb = 0;
  static uint8_t  ws=0;

  // wait for the conversion to complete:
  while (ADCSRA & _BV(ADSC) )
    ;
  uint16_t  adcVal = (ADCL|(ADCH << 8));  // read 16 bits from the ADC

  switch(adcNum)
  {
    case 0:  // ADC 0 is on physical pin 1
      // The reset pin is active so, we only have half of the range (~512-1023)
      // we'll leave a 'dead zone' too
      if (adcVal < 768)
      {
          adcVal = 768;
      }
      adcVal -= 768;        // now we have 0-255

      // Perturb the main waveform randomly, but with a degree
      // of control
      if (adcVal != 0)
      {
        if (--perturb == 0)
        {
           perturb = wsRnd8();
          if (perturb < adcVal)
          {
            ws = perturb;
          }
        }
      }
      else
      {
          ws = 0;       // reset wave to a known state
      }
      break;

    case 1:   // ADC 1 is on physical pin 7
      waveSelect = (ws + (adcVal >> 7)) & 0x07;          // gives us 0-7
      wave1 = waves[waveSelect >> 1];                       // 0-3
      wave2 = waves[(waveSelect >> 1) + (waveSelect & 1)];  // 0-4
      break;

    case MAINKNOB:   // Main Oscillator (fundamental) frequency
      pi_sync = pgm_read_word(&octaveLookup[adcVal]);
      break;

    case SECONDARYKNOB:   // Secondary Oscillator ('resonance') frequency
      pi = pgm_read_word(&octaveLookup[adcVal]);
      break;
  }

  // next time we're dealing with a different channel; calculate which one:
  adcNum++;
  adcNum %= 4;  // we're using all 4 ADC inputs

  // Start the ADC off again, this time for the next oscillator
  // it turns out that simply setting the MUX to the ADC number (0-3)
  // will select that channel, as long as you don't want to set any other bits
  // in ADMUX of course. Still, that's simple to do if you need to.
  ADMUX  = adcNum;      // select the correct channel for the next conversion
  ADCSRA |= _BV(ADSC);  // ADCSRAVAL;
}

// To calculate lookups into the '1024 entry' wavetable
// We shift the 16-bit phase increment by 6 leaving a number in the range 0-1023 (0-0x3ff)
#define FRACBITS (6u)

// This ISR is running at the rate specified by SR (e.g 50kHz)
void
wsAudioLoop(void)
{
  static uint8_t sample = 0;

  // Output the sample first so that jitter is minimised
  wsWriteToPWM(sample);

  // increment the phase counter
  phase += pi;

  uint16_t old_sync = phase_sync;
  phase_sync += pi_sync;
  if (phase_sync < old_sync)
  {
    wsToggleOutput(wsOut2);     // Sub-oscillator
    phase = 0;
  }

  // By shifting the 16 bit number by 6, we are left with a number
  // in the range 0-1023 (0-0x3ff)
  uint16_t p = (phase) >> FRACBITS;

  // look up the output-value based on the current phase counter (truncated)
  // to save wavetable space, we play the wavetable forward (first half),
  // then backwards (and inverted)
  uint16_t ix = p < WTSIZE ? p : ((2*WTSIZE-1) - p);

  // envelope stuff
  uint16_t pp = (phase_sync) >> (FRACBITS+1);
  uint8_t  env = -pgm_read_byte(&ramp[pp]); // 0 --> 0x7f, 7 bits. Also invert the ramp to get a down-ramp!


  uint8_t s1 = pgm_read_byte(&wave1[ix]);
  uint8_t s2 = pgm_read_byte(&wave2[ix]);
  uint16_t s = s1 + s2 - 0x100;         // 9 bits and  remove the 'dc offset'

  uint16_t product = s * env;          // 9 bits * 7 bits = 16 bits
  product = (product + 0x80) + 0x8000;  // re-introduce the DC offset, but also round the number
  sample = product >> 8;

  // invert the wave for the second half
  sample = (p < WTSIZE ? -sample : sample);

}