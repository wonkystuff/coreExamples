/*
 * Polyphonic Ramp-wave generator.
 * Output 1 - Ramp waves;
 * Output 2 - Square sub-oscillator (octave below oscillator 1)
 *
 * Controls:
 *   Knob I   :: <not used>
 *   Knob II  :: Pitch 1
 *   Knob III :: Pitch 2
 *   Knob IV  :: Pitch 3
 *
 * modified Mar 2021  by John Tuffen
 *
 * This example code is in the public domain.
 */

#include "wonkystuffCommon.h"

// the setup function runs once when you press reset or power the board
void
setup(void)
{
  wsInit();                 // general initialisation
  wsInitPWM();              // We're using PWM here
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

#define NUMVOICES 3

typedef struct {
  uint16_t phase;
  uint16_t phase_inc;
} accumulator_t;

volatile accumulator_t accum[NUMVOICES];

// the loop function runs over and over again forever
void
loop(void)
{
  accum[0].phase_inc = wsFetchOctaveLookup(analogRead(wsKnob2));
  accum[1].phase_inc = wsFetchOctaveLookup(analogRead(wsKnob3));
  accum[2].phase_inc = wsFetchOctaveLookup(analogRead(wsKnob4));
}

// This ISR is running at the rate specified by SR (e.g 50kHz)
void
wsAudioLoop(void)
{
  uint16_t oldPhase = accum[0].phase;
  uint8_t outVal = 0;

  int i;
  for(i=0; i< NUMVOICES;i++)
  {
    outVal += accum[i].phase >> 10;
    accum[i].phase += accum[i].phase_inc;   // move the oscillator's accumulator on
  }

  wsWriteToPWM(outVal);

  // If the new value of phase is smaller than it
  // was, then we have completed a ramp-cycle, so
  // change the state of output 2 - this gives us
  // a square wave an octave down from output 1.
  if (accum[0].phase < oldPhase)
  {
    wsToggleOutput(wsOut2);
  }
}
