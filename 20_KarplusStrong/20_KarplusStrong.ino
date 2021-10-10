/*
 * Karplus-Strong synthesis example
 *
 * Output 1 - wavetable output;
 * Output 2 - Square sub-oscillator
 *
 * Controls:
 *   Knob I   :: Detune
 *   Knob II  :: Base pitch (4 oscillators)
 *   Knob III :: relative oscillators #1 (2 oscillators)
 *   Knob IV  :: relative oscillators #2 (2 oscillators)
 *
 * modified Mar 2021  by John Tuffen
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
  uint8_t stimType = analogRead(wsKnob2) >> 7;
  uint8_t stimAmp = analogRead(wsKnob3) >> 7; // gives us 0-7 from 3 bits.
  static uint8_t lastStimAmp;

  accum.phase_inc = pgm_read_word(&octaveLookup[analogRead(wsKnob4)]);

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
        case 0:
          v = i < 128 ? (i*2) - 128 : ((255-i)*2)-128;
          break;
        case 4:
          v = i-128;             // ramp
          break;
        case 7:
          v = (i<128) ? -128 : 127;  // square
          break;
        default:
          v = wsRnd8() - 128;  // noise
          break;
      }
      waveTable[i] += v >> stimShift;
    }
  }
  lastStimAmp = stimAmp;
}

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
