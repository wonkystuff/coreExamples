/*
 * Polyphonic Ramp-wave generator.
 * Output 1 - Ramp waves;
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

// For speed we place the single wavetable in RAM,
// but this will need initialising by our startup
// code.
#define WTSIZE  128u
const uint8_t sine[WTSIZE] PROGMEM = {
  0x80, 0x86, 0x8c, 0x92, 0x98, 0x9e, 0xa4, 0xaa, 0xb0, 0xb6, 0xbb, 0xc1, 0xc6, 0xcb, 0xd0, 0xd5, 
  0xd9, 0xde, 0xe2, 0xe6, 0xe9, 0xec, 0xf0, 0xf2, 0xf5, 0xf7, 0xf9, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 
  0xff, 0xfe, 0xfe, 0xfd, 0xfc, 0xfb, 0xf9, 0xf7, 0xf5, 0xf2, 0xf0, 0xec, 0xe9, 0xe6, 0xe2, 0xde, 
  0xd9, 0xd5, 0xd0, 0xcb, 0xc6, 0xc1, 0xbb, 0xb6, 0xb0, 0xaa, 0xa4, 0x9e, 0x98, 0x92, 0x8c, 0x86, 
  0x80, 0x79, 0x73, 0x6d, 0x67, 0x61, 0x5b, 0x55, 0x4f, 0x49, 0x44, 0x3e, 0x39, 0x34, 0x2f, 0x2a, 
  0x26, 0x21, 0x1d, 0x19, 0x16, 0x13, 0x0f, 0x0d, 0x0a, 0x08, 0x06, 0x04, 0x03, 0x02, 0x01, 0x01, 
  0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x06, 0x08, 0x0a, 0x0d, 0x0f, 0x13, 0x16, 0x19, 0x1d, 0x21, 
  0x26, 0x2a, 0x2f, 0x34, 0x39, 0x3e, 0x44, 0x49, 0x4f, 0x55, 0x5b, 0x61, 0x67, 0x6d, 0x73, 0x79, 
  };

uint8_t waveTable[WTSIZE];

#define NUMVOICES 8

typedef struct {
  uint16_t phase;
  uint16_t phase_inc;
} accumulator_t;

// the setup function runs once when you press reset or power the board
void
setup(void)
{
  // Copy wavetable to RAM buffer
  int i;
  for(i=0; i<WTSIZE;i++)
  {
    waveTable[i] = pgm_read_byte(&sine[i])/NUMVOICES; // ensure that when we add up all of the
                                                      // voices in the output, they will not
                                                      // exceed 8 bits (0-255)
  }
  
  wsInit();                 // general initialisation
  wsInitPWM();              // We're using PWM here
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

volatile accumulator_t accum[NUMVOICES];

// the loop function runs over and over again forever
void
loop(void)
{
  uint16_t tmp = analogRead(wsKnob1);
  uint8_t offs;
  if (tmp < 768)
  {
    offs = 0;
  } else {
    offs = (tmp-768) >> 3;
  }

  accum[0].phase_inc = wsFetchOctaveLookup(analogRead(wsKnob2));
  accum[1].phase_inc = accum[0].phase_inc/2;
  accum[2].phase_inc = accum[0].phase_inc+offs;
  accum[3].phase_inc = accum[0].phase_inc-offs;

  accum[4].phase_inc = accum[0].phase_inc * ((analogRead(wsKnob3) >> 7)+1) + offs; // 3 bits: 0-7
  accum[5].phase_inc = accum[4].phase_inc/2;

  accum[6].phase_inc = accum[0].phase_inc * ((analogRead(wsKnob4) >> 7)+1) - offs;
  accum[7].phase_inc = accum[6].phase_inc/2;

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
    outVal += waveTable[accum[i].phase >> 9]; // Wavetable is 128 entries, so shift the
                                              // 16bit phase counter to leave us with 7bits
                                              // with which to index into the table
    accum[i].phase += accum[i].phase_inc;     // move the oscillator's accumulator on
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
