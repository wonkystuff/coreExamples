// Version of 'Bernoulli Gate' firmware by duddex.
// Original post can be found here: https://forum.aemodular.com/thread/1791/grains-bernoulli-gate
//
// Translated for core1.æ by J Tuffen, 2021
//
// (It works, but I may rewrite it later!)
//
// Inputs:
// * Input to cv-b (turn knob B fully counter-clockwise)
// * Threshold control on cv-c (knob C)
//
// outputs:
// * m-c
// * s-c


void
setup()
{
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
}

boolean gate = false;
boolean oldgate = false;

void
loop()
{
  // Check for gate on core.æ input B
  // "analogRead()" returns values between 0 and 1023
  // If the value is bigger than 700, this is considered as "gate on"
  gate = analogRead(A1) > 700; 

  // React only if state changed
  if (oldgate != gate)
  {
    if (gate)
    {
      // Output probability depends on the value of "knob C":
      // -> The more the knob is turned to the left, the more "M" will be triggered
      // -> The more the knob is turned to the right, the more "S" will be triggered
      if (random(1024) > analogRead(A3))
      { 
        // send gate to "M"
        digitalWrite(1, HIGH);
      }
      else
      {
        // Send gate to "S".
        digitalWrite(0, HIGH);
      }
    }
    else
    {
      // no gate on input "A" -> set all outputs to zero
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
    }
    oldgate = gate;
  }
}
