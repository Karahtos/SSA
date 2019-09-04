//#include <LiquidCrystal_I2C.h>


//LiquidCrystal_I2C lcd(0x27, 16, 4);
int i = 0;
int x = 0;
int OK = 0;

//Testsignal hat 100Hz

int sinPWM[] = {1, 2, 5, 7, 10, 12, 15, 17, 19, 22, 24, 27, 30, 32, 34, 37, 39, 42,
                44, 47, 49, 52, 54, 57, 59, 61, 64, 66, 69, 71, 73, 76, 78, 80, 83, 85, 88, 90, 92, 94, 97, 99,
                101, 103, 106, 108, 110, 113, 115, 117, 119, 121, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146,
                148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 169, 171, 173, 175, 177, 178, 180, 182, 184, 185, 187, 188, 190, 192, 193,
                195, 196, 198, 199, 201, 202, 204, 205, 207, 208, 209, 211, 212, 213, 215, 216, 217, 219, 220, 221, 222, 223, 224, 225, 226, 227,
                228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 237, 238, 239, 240, 240, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246,
                247, 247, 247, 248, 248, 248, 248, 249, 249, 249, 249, 249, 255, 255, 255, 255, 249, 249, 249, 249, 249, 248,
                248, 248, 248, 247, 247, 247, 246, 246, 245, 245, 244, 244, 243, 243, 242, 242, 241, 240, 240, 239, 238, 237, 237, 236, 235, 234,
                233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 217, 216, 215, 213, 212, 211, 209, 208, 207, 205, 204,
                202, 201, 199, 198, 196, 195, 193, 192, 190, 188, 187, 185, 184, 182, 180, 178, 177, 175, 173, 171, 169, 168, 166, 164, 162, 160,
                158, 156, 154, 152, 150, 148, 146, 144, 142, 140, 138, 136, 134, 132, 130, 128, 126, 124, 121, 119, 117, 115, 113, 110, 108, 106,
                103, 101, 99, 97, 94, 92, 90, 88, 85, 83, 80, 78, 76, 73, 71, 69, 66, 64, 61, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 30,
                27, 24, 22, 19, 17, 15, 12, 10, 7, 5, 2, 1
               };

//int Mic0 = PIN0;
//int Mic1 = PIN1;  //hier noch vlt über anderen Datentypen überlegen
//int Mic2 = PIN2;
//int Mic3 = pin3;

short valMic0;    //short weil es 2^13 ADC auflösung hat, short 2^16 darstellen kann
short valMic1;
short valMic2;
short valMic3;

void setup() {
  //  lcd.init();
  //  lcd.backlight();

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  cli();// stop interrupts
  TCCR0A = 0; //reset the value
  TCCR0B = 0; //reset the value
  TCNT0 = 0; //reset the value
  //0b allow me to write bits in binary
  TCCR0A = 0b10100001; //phase correct pwm mode
  TCCR0B = 0b00000001; //no prescaler
  TCCR1A = 0; //reset the value
  TCCR1B = 0; //reset the value
  TCNT1 = 0; //reset the value
  OCR1A = 250; // compare match value
  OCR1B = 30;
  TCCR1B = 0b00001001; //WGM12 bit is 1 and no prescaler
  TIMSK1 |= (1 << OCIE1A);
  sei();// enable interrupts
}
ISR(TIMER1_COMPA_vect) { // interrupt when timer 1 match with OCR1A value
  if (i > 313 && OK == 0) { // final value from vector for pin 6
    i = 0; // go to first value of vector
    OK = 1; //enable pin 5
  }
  if (i > 313 && OK == 1) { // final value from vector for pin 5
    i = 0; //go to firs value of vector
    OK = 0; //enable pin 6

  }
  x = sinPWM[i]; // x take the value from vector corresponding to position i(i is zero indexed)
  i = i + 1; // go to the next position
  if (OK == 0) {
    OCR0B = 0; //make pin 5 0
    OCR0A = x; //enable pin 6 to corresponding duty cycle
  }
  if (OK == 1) {
    OCR0A = 0; //make pin 6 0
    OCR0B = x; //enable pin 5 to corresponding duty cycle
  }
}

//_________________________________________________
// 4 ADC
// 1 DAC
// bluetooth kommunikation zur app
// LCD display
// testsignal kabel zur box
// verschiedene Knöpfe als eingabe für Testsignal auswählen
//_________________________________________________________
//}

void loop() {
  //
  //  valMic0 = analogRead(PIN);
  //  valMic1 = analogRead(PIN);
  //  valMic2 = analogRead(PIN);
  //  valMic3 = analogRead(PIN);
  //
  //  int Display1(short valMic0, short valMic1, short valMic2, short valMic3);
  //  // hier wenn knopf gedruckt dann auf Display 2 wechseln für Batteriestand des gerätes
  //
  //}
  //
  ////Unterprogramme ------------------------------------------------------------------
  //
  //int Display1(short valMic0, short valMic1, short valMic2, short valMic3) {
  //  lcd.setCursor(0, 0);
  //  lcd.print("valMic0");
  //  lcd.setCursor(0, 1);
  //  lcd.print("valMic1");
  //  lcd.setCursor(0, 2);
  //  lcd.print("valMic2");
  //  lcd.setCursor(0, 3);
  //  lcd.print("valMic3");
  //  //möglicherweise einstellen wie oft es refreshen soll
  //}
  //
  //int Display2_BatteryCharge() { //kp was hier übergeben werden muss um Batterie stand zu messen);
  //  //https://www.instructables.com/id/Arduino-Battery-Charge-Monitor/
  //  //Batterie Spannung auslesen (schauen ob es die Spannung von Batterie aushält)
  //}
  //
  int Testsignal() {
    cli();// stop interrupts
    TCCR0A = 0; //reset the value
    TCCR0B = 0; //reset the value
    TCNT0 = 0; //reset the value
    //0b allow me to write bits in binary
    TCCR0A = 0b10100001; //phase correct pwm mode
    TCCR0B = 0b00000001; //no prescaler
    TCCR1A = 0; //reset the value
    TCCR1B = 0; //reset the value
    TCNT1 = 0; //reset the value
    OCR1A = 250; // compare match value
    OCR1B = 30;
    TCCR1B = 0b00001001; //WGM12 bit is 1 and no prescaler
    TIMSK1 |= (1 << OCIE1A);
    sei();// enable interrupts
  }
  ISR(TIMER1_COMPA_vect) { // interrupt when timer 1 match with OCR1A value
    if (i > 313 && OK == 0) { // final value from vector for pin 6
      i = 0; // go to first value of vector
      OK = 1; //enable pin 5
    }
    if (i > 313 && OK == 1) { // final value from vector for pin 5
      i = 0; //go to firs value of vector
      OK = 0; //enable pin 6

    }
    x = sinPWM[i]; // x take the value from vector corresponding to position i(i is zero indexed)
    i = i + 1; // go to the next position
    if (OK == 0) {
      OCR0B = 0; //make pin 5 0
      OCR0A = x; //enable pin 6 to corresponding duty cycle
    }
    if (OK == 1) {
      OCR0A = 0; //make pin 6 0
      OCR0B = x; //enable pin 5 to corresponding duty cycle
    }
  }

  //  //https://www.arduino.cc/en/Tutorial/DueSimpleWaveformGenerator
  //  //http://www.infomechatronix.ch/embedded/68-pwm-sinus-arduino
  //  //testen und aufschreiben was besser ist: Stützstellen oder PWM
  //  //https://www.eprojectszone.com/how-to-generate-a-sine-wave-from-arduino-or-atmega-328/
  //
  //}
  //
  //int Bluetooth() {
  //  //http://suavop.blogspot.com/2013/12/hc-05-bluetooth-communication-with.html
  //
}
//
//___________________________________________________________________________________
//void EEPROM_write(int address, char data )
//{
//  while (EECR & (1 << EEPE));
//  EECR &= ~((1 < EEPM1) | (1 << EEPM0));
//  EEAR = address;
//  EEDR = data;
//  EECR |= (1 << EEMPE);
//  EECR |= (1 << EEPE);
//
//}
