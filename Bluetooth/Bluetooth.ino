// The HC-06 defaults to AT mode when first powered on.
// The default baud rate is 9600
// The Hc-06 requires all AT commands to be in uppercase. NL+CR should not be added to the command string
//


//Does work is named SSA

//Spannung könnte nicht hoch genug sein, durch den Spannungsteiler. Nachschauen in Datenblatt und dann mit richtiger Spannung testen.
//HC 05 app für kommunikation


#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-06 TX to the Arduino RX on pin 2.
// Connect the HC-06 RX to the Arduino TX on pin 3 through a voltage divider.
//


void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");

  // HC-06 default serial speed is 9600
  BTserial.begin(9600);//38400 oder 9600
}

void loop()
{

  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTserial.available())
  {
    Serial.write(BTserial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available())
  {
    //Serial.write("Test");
    BTserial.write(Serial.read());
  }

}
