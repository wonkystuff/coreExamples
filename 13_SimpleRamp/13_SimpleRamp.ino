/*
 * Simple Ramp-wave generator.
 * Output 1 - Ramp wave;
 * Output 2 - Square sub-oscillator
 *
 * Controls:
 *   Knob III :: Pitch
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

  pinMode(wsOut1, OUTPUT);  // output 1
  pinMode(wsOut2, OUTPUT);  // output 2
  
  wsInitPWM();
  wsInitAudioLoop(20000);   // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

volatile uint16_t phase_inc = 0x80;

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
  uint16_t oldPhase = phase;

  phase += phase_inc;   // move the oscillator's accumulator on

  wsWriteToPWM(phase >> 8);

  // If the new value of phase is smaller than it
  // was, then we have completed a ramp-cycle, so
  // change the state of output 2 - this gives us
  // a square wave an octave down from output 1.
  if (phase < oldPhase)
  {
    wsToggleOutput(wsOut2);
  }
}
