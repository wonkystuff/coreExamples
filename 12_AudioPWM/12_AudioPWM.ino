/*
 * Yet another square-wave generator, but this one now
 * allows the with of the output square wave to be changed
 * Output 2 is the same pitch square wave at full
 * volume
 *
 * Controls:
 *   Knob II  :: Output Pulse Width
 *   Knob III :: Pitch
 *   Knob IV  :: Amplitude
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
  wsInitPWM();              // output 1 is now controlled by PWM
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

uint16_t phase_inc;
uint8_t  ampl;
uint16_t width;

// the loop function runs over and over again forever
void
loop(void)
{
  width     = analogRead(wsKnob2) << 6; // value between 0 and 65535
  phase_inc = (analogRead(wsKnob3) + 1) << 2;
  ampl      = analogRead(wsKnob4) >> 2;       // values between 0-255
}

// This ISR is running at the rate specified by SR (e.g 50kHz)
void
wsAudioLoop(void)
{
  static uint16_t phase  = 0;
  phase += phase_inc;   // move the oscillator's accumulator on

  if (phase > width)
  {
    wsWriteToPWM(ampl);
    wsPinSet(wsOut2);
  }
  else
  {
    wsWriteToPWM(0);
    wsPinClear(wsOut2);
  }
}