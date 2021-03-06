/*
 * SImplest square-wave generator - emits the same signal
 * on both audio outputs.
 *
 * Controls:
 *   Knob III :: Pitch
 *
 * modified Feb 2021  by John Tuffen
 *
 * This example code is in the public domain.
 */

#include "wonkystuffCommon.h"

// the setup function runs once when you press reset or power the board
void
setup(void)
{
  wsInit();                 // general initialisation
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

uint16_t phase_inc = 0x80;

// the loop function runs over and over again forever
void
loop(void)
{
  phase_inc = (analogRead(wsKnob3) + 1) << 2;
}

// This ISR is running at the rate specified by SR (e.g 50kHz)
void
wsAudioLoop(void)
{
  static uint16_t phase  = 0;
  phase += phase_inc;   // move the oscillator's accumulator on

  if (phase > 0x8000)   // half way between 0 and 0xffff gives us a 50% duty-cycle
  {
    wsPinSet(wsOut1);
    wsPinSet(wsOut2);
  }
  else
  {
    wsPinClear(wsOut1);
    wsPinClear(wsOut2);
  }
}