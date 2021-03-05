/*
  Modified Blink - but for the Core1 hardware

  Turns an LED on for some time, then off for some time, repeatedly.

  modified 8 May 2014   by Scott Fitzgerald
  modified 2 Sep 2016   by Arturo Guadalupi
  modified 8 Sep 2016   by Colby Newman
  modified 23 Feb 2021  by John Tuffen

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void
setup(void)
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);       // PWM output pin
}

// the loop function runs over and over again forever
void
loop(void)
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // read the value from the sensor:
  uint16_t del = analogRead(A1);

  delay(del);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  del = analogRead(A3);
  delay(del);                       // wait for a second
}
