float phase = 0.0;
float twopi = 3.14159 * 2;
elapsedMicros usec = 0;

void setup() {
  analogWriteResolution(12);
}

void loop() {
  float val = sin(phase) * 2000.0 + 2050.0;
  analogWrite(A14, (int)val);
  phase = phase + 0.02;
  if (phase >= twopi) phase = 0;
  while (usec < 500) ; // wait
  usec = usec - 500;
}


// code von https://www.pjrc.com/teensy/teensy31.html DAC 

//code mit registern https://forum.pjrc.com/threads/25395-Teensy-Quick-Reference-Code-Examples-Tips-and-Tricks
