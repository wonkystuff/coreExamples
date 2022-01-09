#include "wonkystuffCommon.h"

extern const uint8_t vcdoWaves[32][64];
uint16_t          phase;      // The accumulated phase (distance through the wavetable)
uint16_t          phase_inc;  // wavetable current phase increment (how much phase will increase per sample)
uint8_t           bank;
uint8_t           wave;
const uint8_t     *wavePtr;

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
  wave = (analogRead(wsKnob4) << 1) >> 8; // wave is 3 bits (0-7)

  wavePtr = vcdoWaves[(bank*8)+wave];
}

        
uint8_t outVal;
uint8_t prevVal;
void
wsAudioLoop(void)
{
  wsWriteToPWM((outVal+prevVal)/2);
  phase += phase_inc;

  uint8_t p = phase >> 10;  // wavetable is indexed with 6 bits
  prevVal = outVal;
  outVal = pgm_read_byte(&wavePtr[p]);
}  
