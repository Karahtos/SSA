
// NJarpa
// LCD 16x2 Multiple screens example
http://www.carobot.cc/how-to/lcd-16x2-or-20x4-usage-guide/
//libarary einbinden 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
//Counter to change positions of pages

int page_counter=1 ;       //To move beetwen pages


//-------Pins-----//
int up = 8;               //Up button
int down = 10;           //Down button
//---------Storage debounce function-----//
boolean current_up = LOW;          
boolean last_up=LOW;            
boolean last_down = LOW;
boolean current_down = LOW;
        

void setup() {
    lcd.init();
  lcd.backlight();

}


   //---- De-bouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}


void loop() {

current_up = debounce(last_up, up);         //Debounce for Up button
current_down = debounce(last_down, down);   //Debounce for Down button

//----Page counter function to move pages----//

//Page Up
    if (last_up== LOW && current_up == HIGH){  //When up button is pressed
      lcd.clear();                     //When page is changed, lcd clear to print new page  
      if(page_counter <3){              //Page counter never higher than 3(total of pages)
      page_counter= page_counter +1;   //Page up
      
      }
      else{
      page_counter= 3;  
      }
  }
  
    last_up = current_up;

//Page Down
    if (last_down== LOW && current_down == HIGH){ //When down button is pressed
      lcd.clear();                     //When page is changed, lcd clear to print new page    
      if(page_counter >1){              //Page counter never lower than 1 (total of pages)
      page_counter= page_counter -1;   //Page down
      
      }
      else{
      page_counter= 1;  
      }
  }
    
    last_down = current_down;

//------- Switch function to write and show what you want---// 
  switch (page_counter) {
   
    case 1:{     //Design of home page 1
      lcd.setCursor ( 0, 0 );
      lcd.print("This is");
      lcd.setCursor ( 0, 1 );
      lcd.print(" Home Page");
    }
    break;

    case 2: { //Design of page 2 
     lcd.setCursor(0,0);
     lcd.print("222");
     lcd.setCursor(0,1);
     lcd.print("2222");
    }
    break;

    case 3: {   //Design of page 3 
     lcd.setCursor(1,0);
     lcd.print("333");
     lcd.setCursor(4,1);
     lcd.print("3333");
    }
    break;
    
  }//switch end
  
}//loop end
