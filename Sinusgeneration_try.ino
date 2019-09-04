#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

void setup(){
  startMozzi(); // uses the default control rate of 64, defined in mozzi_config.h
  aSin.setFreq(440); // set the frequency
}


void updateControl(){}


int updateAudio(){
  // this would make more sense with a higher resolution signal
  // but still benefits from using HIFI to avoid the 16kHz pwm noise
  return aSin.next()<<6; // 8 bits scaled up to 14 bits
}


void loop(){
  audioHook(); // required here
}
