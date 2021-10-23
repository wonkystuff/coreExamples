/*
 * Karplus-Strong synthesis example. This is an early 'physical-model'
 * synthesis method from 1983, used to synthesise plucked-string sounds.
 * More information can be found here:
 *    https://en.wikipedia.org/wiki/Karplus–Strong_string_synthesis
 *
 * Output 1 - audio output;
 * Output 2 - not used
 *
 * Controls:
 *   Knob I   :: not used
 *   Knob II  :: Stimulation type (noise, ramp, square, triangle)
 *   Knob III :: trigger input
 *   Knob IV  :: pitch
 *
 * modified Oct 2021  by John Tuffen
 *
 * This example code is in the public domain.
 */

#include "wonkystuffCommon.h"

// For speed the single wavetable is in RAM, but we need
// to initialise it in the startup code. The following ROM
// bytes are the initialiser - a single-cycle of a sinewave.
// Other waveshapes can of course be calculated and placed here.
//
// Since the initialisation is not time-critical, it is of course
// also possible to do the mathematical calculation of the
// initialiser in the setup() function...

#define WTSIZE  256u

uint8_t waveTable[WTSIZE];

typedef struct {
  uint16_t phase;
  uint16_t phase_inc;
} accumulator_t;

// the setup function runs once when you press reset or power the board
void
setup(void)
{
  // Copy wavetable to RAM buffer
  uint16_t i;
  for(i=0; i<WTSIZE;i++)
  {
    waveTable[i] = wsRnd8();    // prefill with noise
  }

  wsInit();                 // general initialisation
  wsInitPWM();              // We're using PWM here
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

volatile accumulator_t accum;

// the loop function runs over and over again forever
void loop()
{
  uint8_t stimType = analogRead(wsKnob2) >> 8;  // gives us 0-3 from 2 bits.
  uint8_t stimAmp = analogRead(wsKnob3) >> 7;   // gives us 0-7 from 3 bits.
  static uint8_t lastStimAmp;

  // divide the phase increment value by 2 here otherwise things get very squeaky/allias-y
  accum.phase_inc = pgm_read_word(&octaveLookup[analogRead(wsKnob4)])/2;

  if ((stimAmp != 0) &&
      (lastStimAmp < stimAmp))
  {
    int i;
    uint8_t stimShift = 7 - stimAmp;  // 7-0
    for(i=0; i<WTSIZE;i++)
    {
      char v=0;
      switch (stimType)
      {
        // 'periodic' inputs are half amplitude because otherwise they're pretty loud
        case 1:         // ramp
          v = (i-128)/2;
          break;
        case 2:         // square
          v = (i<128) ? -64 : 64;
          break;
        case 3:         // triangle
          v = (i < 128 ? (i*2) - 128 : ((255-i)*2)-128)/2;
          break;
        case 0:
        default:
          v = wsRnd8() - 128;  // noise
          break;
      }
      waveTable[i] += v >> stimShift;
    }
  }
  lastStimAmp = stimAmp;
}

// If TWO is defined then two adjacent samples are averaged
// in the algorithm, otherwise 4 are averaged. Fewer samples
// means a longer decay.
#define TWO (1)

// This ISR is running at the rate specified by SR (e.g 50kHz)
void
wsAudioLoop(void)
{
  static char outVal = 0;

  wsWriteToPWM(0x80+ outVal); // write to output before anything variable happens to reduce jitter

#ifdef TWO
  static char lastOut=0;
#else
  static char avBuf[4];
  static int avIdx;
#endif


  uint8_t p = accum.phase >> 8;         // Wavetable is 256 entries, so shift the
                                        // 16bit phase-accumulator value to leave us with 8bits
                                        // with which to index into the table
  outVal = waveTable[p];                // read the wavetable value at the current phase position
#ifdef TWO
  waveTable[p] = (lastOut+outVal)/2;    // write back to the wavetable the average of the last
                                        // output and this output
  lastOut = outVal;
#else
  avBuf[avIdx++] = outVal;
  avIdx &=0x03;
  waveTable[p] = avBuf[0]/4 + avBuf[1]/4 + avBuf[2]/4 + avBuf[3]/4;
#endif

  accum.phase += accum.phase_inc;       // move the oscillator's phase-accumulator on
}
