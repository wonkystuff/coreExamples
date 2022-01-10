/*
 * Software re-creation of the Digisound-80 VCDO module (See http://www.digisound80.co.uk/digisound/modules/80-21.htm)
 * 
 * This is a very lo-fi wavetable oscillator with 32 waveforms arranged in 4 banks of 8 waves.
 * The following data was extracted from the DigiSound VCDO
 * EPROM hex file found at http://donaupeter.de/synth/VCDO-Digisound/VCDO-Digisound.htm
 *
 * Each waveform contains a mere 64 entries.
 * 
 * Output 1 - wavetable output;
 *
 * Controls:
 *   Knob I   :: manual pitch adjust
 *   Knob II  :: Pitch CV 
 *   Knob III :: Bank Select (1 of 4)
 *   Knob IV  :: Wave select (1 of 8)
 *
 * modified January 2022  by John Tuffen
 *
 * This example code is in the public domain.
 */

#include "wonkystuffCommon.h"

extern const uint8_t vcdoWaves[32][64]; // Waves are in the adjacent ino file
uint16_t          phase_inc;            // wavetable current phase increment (how much phase will increase per sample)
const uint8_t    *wavePtr;              // points to the selected waveform to minimise calculation in the sample-calculation

void
setup(void)
{

  wsInit();                 // general initialisation
  wsInitPWM();              // We're using PWM here
  wsInitAudioLoop();        // initialise the timer to give us an interrupt at the sample rate
                            // make sure to define the wsAudioLoop function!
}

// the loop function runs over and over again forever
void
loop(void)
{
  uint16_t base = wsFetchOctaveLookup5(0);
  uint16_t po = analogRead(wsKnob1) > 700 ? analogRead(wsKnob1) : 700;
  uint16_t offs = wsFetchOctaveLookup5(po - 700) - base;  // so the pitch offset can start at zero

  uint8_t  bank = analogRead(wsKnob3) >> 8; // bank is 2 bits (0-3)
  uint8_t  wave = (analogRead(wsKnob4) << 1) >> 8; // wave is 3 bits (0-7)

  // Get the required phase increment to match the requested pitch
  phase_inc = offs + wsFetchOctaveLookup5(analogRead(wsKnob2));
  wavePtr = vcdoWaves[(bank*8)+wave];   // update the pointer to the active wave
}
        
void
wsAudioLoop(void)
{
  static uint16_t phase;      // The accumulated phase (distance through the wavetable)
  static uint8_t  outVal;     // the output value persists between invocations of the audio loop

  wsWriteToPWM(outVal);       // output the sample first to remove jitter
  phase += phase_inc;         // move the phase counter on

  uint8_t p = phase >> 10;    // wavetable is indexed with 6 bits - the highest 6 bits from the 16 bit phase accumulator

  outVal = pgm_read_byte(&wavePtr[p]);  // now fetch the sample...
}  
