#include <MicroView.h>

const int button0Pin = 0;
const int button1Pin = 1;
boolean pressed0 = false;
boolean pressed1 = false;
  int valueToPrint = 0;


void setup()
{
  uView.begin();
  uView.print("HelloWorld");
  pinMode(button0Pin, INPUT);
  pinMode(button1Pin, INPUT);
}

void loop()
{
  
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
    

  uView.print(valueToPrint);
  
  }
  /*
  if(digitalRead(button0Pin)){
    lcd.print("1   ");
  }
  else{
    lcd.print("0   ");
  }*/
