# Atari Punk Console Emulation

This one is something I’ve been thinking about for a while — it’s a rough approximation to the famous Atari Punk Console!
Split into two parts, there’s a square-wave oscillator as well as a pulse generator; when you trigger the pulse generator
with the square wave generator you get the characteristic ‘stepped pulse’ output. In addition, this version also has a
ramp output mode (selected by the ‘mode’ control - knob a).

It is of course possible to connect the output of a VCO to the trigger input if you want to do fancy things like play tunes!

## Outputs:

- m-c/m-a: pulse-generator (monostable) output (or ramp output)
- s-c/s-a: square wave clock output

## Inputs

- Control a: mode (pulse or ramp output on m-c/m-a);
- Input b: Trigger for pulse/ramp output (knob B should be fully counter-clockwise);
- Control/Input c: Length of pulse/ramp output;
- Control/Input d: Frequency of square-wave output.

