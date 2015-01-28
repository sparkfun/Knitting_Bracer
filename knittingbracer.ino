#include <LiquidCrystal.h>

const int button0Pin = 0;
const int button1Pin = 1;
boolean pressed0 = false;
boolean pressed1 = false;
  int valueToPrint = 0;


LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Start here:");
  pinMode(button0Pin, INPUT);
  pinMode(button1Pin, INPUT);
}

void loop()
{
  lcd.setCursor(0,1);

  if(digitalRead(button0Pin) == 0){
    pressed0 = true;
  }else{
    if(pressed0){
      pressed0 = false;
      valueToPrint ++;
    }
  }
  
  if(digitalRead(button1Pin) == 0){
    pressed1 = true;
  }else{
    if(pressed1){
      pressed1 = false;
      valueToPrint --;
    }
    
  lcd.print("       "); // Erase the largest possible number
  lcd.setCursor(0,1);   // Reset the cursor to the original position
  lcd.print(valueToPrint);
  delay(250); //delay quarter of a second so it doesn't flicker
  }
  /*
  if(digitalRead(button0Pin)){
    lcd.print("1   ");
  }
  else{
    lcd.print("0   ");
  }*/
  
