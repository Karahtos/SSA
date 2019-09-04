/*
 * Author: Anthony Spagnoletti
 * 
 * Arduino Battery Charge Monitor Code
 * 
 */
 
int analogVal = 0;      //stores the value that comes from battery
float volt = 0;         //stores the calculated voltage value 
int timeDelay = 1000;   //duration for LED's to remain on

float Vin;
float Vmax = 6;  
float Vausgabe;
int Vref = 5;     


float berechnung(float analogVal){
      
    Vin = (analogVal * Vref) / 1024;
    Vausgabe = Vin/Vmax *100;
    Serial.print("%Ausgabe: ");
    Serial.println(Vausgabe);
    return Vin; 
  }

  
void setup() {
}

void loop() {
  float x,
  
  // put your main code here, to run repeatedly:
  analogVal = analogRead(A0);//reads the analog pin value
  
   x = berechnung(analogVal);
  
  Serial.print("Vin: ");
  Serial.println(Vin);
  
  
}
