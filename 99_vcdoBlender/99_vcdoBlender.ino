/*
 * Enhanced software re-creation of the Digisound-80 VCDO module (See http://www.digisound80.co.uk/digisound/modules/80-21.htm)
 * 
 * This is a very lo-fi wavetable oscillator with 32 waveforms arranged in 4 banks of 8 waves.
 * The following data was extracted from the DigiSound VCDO
 * EPROM hex file found at http://donaupeter.de/synth/VCDO-Digisound/VCDO-Digisound.htm
 *
 * Each waveform contains a mere 64 entries.
 * 
 * This version differs from the 99_vcdo version in that there are also blended wavetables
 * in between the 8 in each bank (there are 8 intermediate positions, so it could be said
 * that there are actually 64 different waveshapes available - unless my maths is wrong!)
 * 
 * Output 1 - wavetable output;
 *
 * Controls:
 *   Knob I   :: manual pitch adjust
 *   Knob II  :: Pitch CV 
 *   Knob III :: Bank Select (1 of 4)
 *   Knob IV  :: Wave select (1 of 8 with 8 intermediate blends)
 *
 * modified January 2022  by John Tuffen
 *
 * This example code is in the public domain.
 */


#include "wonkystuffCommon.h"

extern const uint8_t vcdoWaves[32][64];
uint16_t       phase;      // The accumulated phase (distance through the wavetable)
uint16_t       phase_inc;  // wavetable current phase increment (how much phase will increase per sample)
uint8_t        bank;
uint8_t        wave;
uint8_t        blend;
const uint8_t *w1;
const uint8_t *w2;

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
  static const uint16_t base = wsFetchOctaveLookup5(0);
  uint16_t po = analogRead(wsKnob1) > 700 ? analogRead(wsKnob1) : 700;
  uint16_t offs = wsFetchOctaveLookup5(po - 700) - base;  // so the pitch offset can start at zero
  phase_inc = offs + wsFetchOctaveLookup5(analogRead(wsKnob2));
  bank = analogRead(wsKnob3) >> 8; // bank is 2 bits (0-3)

  // wave is 3 bits (0-7)
  // blend is 3 bits also
  // www bbb 0000

  uint16_t k4 = analogRead(wsKnob4); 
  wave = (k4 << 1) >> 8;
  blend = k4 >> 4;
  blend &= 0x07;
  // The 'blend' control will blend between adjacent waves - set up their pointers here:
  w1 = vcdoWaves[(bank*8)+wave];
  w2 = vcdoWaves[(bank*8)+((wave+1) % 8)];
}

void
wsAudioLoop(void)
{
  // outVal persists from the last time we were here
  static uint8_t outVal;

  // Write out the audio sample to remove jitter caused by the calculations afterward
  wsWriteToPWM(outVal);

  // Move the phase accumulator forward
  phase += phase_inc;

  uint8_t p = (phase >> 8) >> 2;  // wavetable is only 64 entries, so indexed with 6 bits

  // We know that the blend is between two pointers, so prefetch them here as reading
  // from PROGMEM is time consuming
  uint8_t m = pgm_read_byte(&w1[p]);
  uint8_t s = pgm_read_byte(&w2[p]);
  int i;
  uint16_t sum=0;
  
  // add together 8 numbers, depending on the value of 'blend'
  for(i=0;i<8;i++)
  {
    sum += (i >= blend) ? m : s;
  }

  // we've added together 8 waves, so rescale the sum
  outVal = sum/8;
} 
