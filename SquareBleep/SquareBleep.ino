/*
 * Like Blink, but WITH SOUND! Bleeps at an interval determined
 * by Control 2, with a pitch determined by Control 3
 *
 * modified 25 Feb 2021  by John Tuffen
 *
 * This example code is in the public domain.
 */

#include "wonkystuffCommon.h"


void
wsInit(void)
{    
    PLLCSR |= _BV(PLLE);                // Enable 64 MHz PLL
    delayMicroseconds(100);             // Stabilize
    while (!(PLLCSR & _BV(PLOCK)))
        ;                               // Wait for it...
    PLLCSR |= _BV(PCKE);                // Timer1 source = PLL
}

// Fixed value to start the ADC
// enable ADC, start conversion, prescaler = /64 gives us an ADC clock of 8MHz/64 (125kHz)
#define ADCSRAVAL ( _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1)  | _BV(ADIE) )

void
wsInitPWM(void)
{
    ///////////////////////////////////////////////
    // Set up Timer/Counter1 for 250kHz PWM output
    TCCR1 = 0;                  // stop the timer
    TCNT1 = 0;                  // zero the timer
    GTCCR = _BV(PSR1);          // reset the prescaler
    TCCR1 = _BV(PWM1A) | _BV(COM1A1) | _BV(COM1A0) | _BV(CS10);
    OCR1C = 255;
    OCR1A = 128;                // start with 50% duty cycle on the PWM
    pinMode(PB1, OUTPUT);       // PWM output pin
}

// Base-timer is running at 16MHz
#define F_TIM (16000000L)
#define SRATE (20000)

// Remember(!) the input clock is 64MHz, therefore all rates
// are relative to that.
// let the preprocessor calculate the various register values 'coz
// they don't change after compile time
#if ((F_TIM/(SRATE)) < 255)
#define T1_MATCH ((F_TIM/(SRATE))-1)
#define T1_PRESCALE _BV(CS00)  //prescaler clk/1 (i.e. 8MHz)
#else
#define T1_MATCH (((F_TIM/8L)/(SRATE))-1)
#define T1_PRESCALE _BV(CS01)  //prescaler clk/8 (i.e. 1MHz)
#endif

void
wsInitISR(int sampleRate)
{
    ///////////////////////////////////////////////
    // Set up Timer/Counter0 for sample-rate ISR
    TCCR0B = 0;                 // stop the timer (no clock source)
    TCNT0 = 0;                  // zero the timer
    TCCR0A = _BV(WGM01);        // CTC Mode
    TCCR0B = T1_PRESCALE;
    OCR0A  = T1_MATCH;          // calculated match value
    TIMSK |= _BV(OCIE0A);
}



// the setup function runs once when you press reset or power the board
void
setup(void)
{
  wsInit();             // general initialisation

  wsInitISR(20000);     // initialise the timer to give us an interrupt at the sample rate
                        // make sure to define the ISR!
  pinMode(wsOut1, OUTPUT); // output 1
  pinMode(wsOut2, OUTPUT); // output 2

  sei();                // enable interrupts before we get going
}

uint16_t phase_inc = 0x80;
// because we use timer 0, delay() doesn't work - se we roll our own
volatile uint32_t ticks = 0;

// the loop function runs over and over again forever
void
loop(void)
{
  phase_inc    = analogRead(wsKnob3);

  ticks = 0;
  while (ticks < 50000)
    ticks++;

  phase_inc = 0;  // stop the oscillator!

  ticks = 0;
  while (ticks < 50000)
    ticks++;
}

// This ISR is running at the rate specified by SR (e.g 50kHz)
ISR(wsTimerVector)
{
  static uint16_t phase  = 0;

  phase += phase_inc;   // move the oscillator's accumulator on
  if (phase > 0x8000)   // half way between 0 and 0xffff
  {
    wsPinSet(wsOut1);
  }
  else
  {
    wsPinClear(wsOut1);
  }
}
