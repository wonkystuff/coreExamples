/*
 * Implementation of an Atari Punk Console style thing for Core1.æ.
 * 
 * Outputs:
 *   m-c: monostable output
 *   s-c: square-wave clock output.
 *   
 * Inputs/Controls:
 *   Control a: mode (square or ramp output)
 *   Input b: monostable trigger input (knob B should be fuly counter-clockwise)
 *   Control/Input c: length of monostable pulse (clockwise -> shorter)
 *   Control/Input d: square wave speed (clockwise -> faster)
 */

#include "wonkystuffCommon.h"

// the setup function runs once when you press reset or power the board
void
setup(void)
{
  wsInit();                 // general initialisation
  wsInitPWM();              // output 1 is now controlled by PWM

  PCMSK |= (1 << PCINT2);   // turn on pin-change interrupts on pin PB2
  GIMSK |= (1 << PCIE);     // turns on pin change interrupts

  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

// global vars for communication between idle loop and ISR
volatile uint16_t  clkFreq;           // Actually the clock 'phase increment'
volatile uint16_t  monoLength;        // Length (in ticks) of the output monstable pulse
volatile uint8_t   outMode;

// the loop function runs over and over again forever
void
loop(void)
{
  // OR-ing analogue values with 3 ensures that they are never zero, and also de-jitters to a certain extent
  monoLength = (1023-(analogRead(wsKnob3))) | 0x0003;  // make the monostable time shorten as knob turns clockwise
  clkFreq =  wsFetchOctaveLookup(analogRead(wsKnob4) | 0x0003);
  outMode = analogRead(wsKnob1) > 768; // true/false
}

// Communication between the pin-change interrupt and the audio loop:
volatile uint8_t clockRisingEdgeSeen = 0;

// This ISR is running at the sample rate
void
wsAudioLoop(void)
{
  static uint16_t phase;
  static uint16_t monoTime=0;
  static uint8_t  monoValue=0;

  // output the square clock - set to the value of the top bit of the phase counter
  phase += clkFreq;
  if (phase & 0x8000)
  {
    wsPinSet(wsOut2);
  }
  else
  {
    wsPinClear(wsOut2);
  }

  // output the monostable pulse (or ramp):
  if (outMode)
  {
    // Write out a descending ramp in this mode
    if (monoTime < 0x100)
    {
      wsWriteToPWM(monoTime);
    }
  }
  else
  {
    wsWriteToPWM(monoValue);
  }

  // If the pin is high and we're not in a pulse then we're interested
  if (clockRisingEdgeSeen && (monoTime == 0))
  {
    monoTime = monoLength;
  }
  clockRisingEdgeSeen = 0;
  
  if (monoTime != 0)
  {
    monoTime--;
    monoValue = 255;
  }
  else
  {
    monoValue = 0;
  }
}

// Pin change interrupt - set on state change of I/O. We set this up
// to only be enabled on PCINT2 (PB2) so if we get here we know that
// something happened on PB2
ISR(PCINT0_vect)
{
    // If the pin is currently 'high' then signal to the timing ISR
    // that a clock occurred. This will hopefully do a bit of
    // debouncing for us.
    if (PINB & _BV(PB2))
    {
        clockRisingEdgeSeen = 1;
    }
}
