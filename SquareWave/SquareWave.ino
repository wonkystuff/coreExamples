/* core1_square1 a demo synth for the Wonkystuff core1 board
 *
 * Copyright © 2017-2018  John A. Tuffen
 * Copyright © 2020 John A. Tuffen, Simon Hickinbotham, wonkystuff
 *
 * Questions/queries can be directed to info@wonkystuff.net
 */

#include "wonkystuff.h"

void setup()
{
    wonkystuff_init();

    ///////////////////////////////////////////////
    // Set up the ADC
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

    pinMode(PB0, OUTPUT);       // supplementary oscillator output pin
}

potVal_t var1;
potVal_t var2;

uint16_t phase_inc;

void processPot(potVal_t *valBuf, uint16_t newVal)
{
//    var1 = addToAverage(&val1Buf, ADCREDUX(adcVal, 5));     // 0 <= var1 <= 31 [always used as a shift, so no point in being > 32]

    // Numbers in ranges
    valBuf->raw       = newVal;
    valBuf->byteVal   = ADCREDUX(newVal, 8);
    valBuf->valSeven  = valBuf->byteVal >> 1;
    valBuf->bitNum    = valBuf->valSeven >> 2;

    // individual set bits
    valBuf->bitSet32  = 1 << valBuf->bitNum;
    valBuf->bitSet16  = 1 << (valBuf->bitNum / 2);
    valBuf->bitSet8   = 1 << (valBuf->bitNum / 4);

    // masks
    valBuf->bitMask32 = valBuf->bitSet32 - 1;
    valBuf->bitMask16 = valBuf->bitSet16 - 1;
    valBuf->bitMask8  = valBuf->bitSet8 - 1;
}

/*  The standard arduino 'loop' function is the place where we read the 
 *  potentiometer values. There aren't as many time constraints in this loop
 *  as it 'idles' while 
 */
void loop(void)
{

    /* The core1 has four potentiometers, each hooked up to the four ADC channels (pins
     *  
     */
  
    static uint8_t  adcNum=0;               // declared as static to limit variable scope

    while (ADCSRA & _BV(ADSC) )
        ;                                   // wait for the conversion to complete
    uint16_t  adcVal = (ADCL|(ADCH << 8));  // read 16 bits from the ADC

    adcVal &= ADCRANGE - 1;                 // although we know that the hardware only 10 active bits,
                                            // make it explicit here in case we port this to a 16bit ADC later

    // Now we've grabbed the adcValue, we can start the ADC off again so that
    // it can be converting whilst we deal with the last channel's value.

    // next time we're dealing with a different channel; calculate which one:
    uint8_t thisAdcChannel = adcNum;
    adcNum++;
    adcNum %= NUMADCS;

    // Start the ADC off again, this time for the next oscillator
    // it turns out that simply setting the MUX to the ADC number (0-3)
    // will select that channel, as long as you don't want to set any other bits
    // in ADMUX of course. Still, that's simple to do if you need to.
    ADMUX  = adcNum;      // select the correct channel for the next conversion
    ADCSRA |= _BV(ADSC);  // Start the conversion;

    switch(thisAdcChannel)
    {
        case 0:  // ADC 0 is on physical pin 1
            // The reset pin is active here, we only have half of the range
            if (adcVal < ADCRANGE/2)
            {
                adcVal = ADCRANGE/2;
            }
            adcVal -= ADCRANGE/2;           // now we have 0-511
            adcVal <<= 1 ;                  // stretch to a 10 bit range

            //currentExpression = exprs[ADCREDUX(adcVal, 3)];
            break;

        case 1:
            processPot(&var1, adcVal);
            break;

        case 2:
            processPot(&var2, adcVal);
            break;

        case 3:
            // Control over the pitch of the output sound.
            // Here, we look up an increment to a virtual oscillator,
            // the frequency of which determines when we calculate
            // another byte-beat byte
            phase_inc = pgm_read_word(&octaveLookup[ADCREDUX(adcVal, DACBITS)]);
            //phase_inc = phase_inc >> 10;
            break;
    }
}

// deal with oscillator on the "fast"/master timer
// This ISR is running at the rate specified by SR (e.g 50kHz)
// The actual audio output is only updated when the notional 'audio oscillator' wraps.
ISR(TIM0_COMPA_vect)
{
    static TTYPE t     = 0;  // t is time in nominal 'ticks'. One tick is equivalent to a full cycle of the unheard audio-rate oscillator
    static uint16_t phase = 0;  // phase is incremented every sample interrupt - phase_inc is set using pot 3 — this is the unheard audio oscillator :)

    static bool sqlevel = false;
    uint16_t val = 0;
    uint16_t old_phase = phase;
    phase += phase_inc;

    // If the 'audio-oscillator' has completed a cycle, the phase will now be (near to) zero, so
    // update the tick and recalculate the output sample.
    if (phase < old_phase)
    {
        // phase has wrapped - one more cycle done
        // We only do this when we absolutely need to because it can take some time to
        // compute. If this were a real-time system, we'd want to ensure that all
        // calculations were done within the allotted time. We could slow down the sample
        // rate of course.

         if(sqlevel){
            sqlevel = false;
            //digitalWrite(PB1, HIGH);
            val = 0;
         }
        else{
            sqlevel = true;
            //digitalWrite(PB1, LOW);
            val = 65535; 
        }
        OSCOUTREG = val;
    }
}
