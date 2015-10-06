/****************************************************************************
Knitting Bracer MV Demo
Liz Neuhalfen @ SparkFun Electronics
September 2015
https://github.com/sparkfun/Knitting_Bracer

This sketch goes with the SparkFun Live Demo of the Knitting Bracer.
You can see the project video here:https://www.youtube.com/watch?v=Mj5dSqC7Hgc

Wishlist is here: https://www.sparkfun.com/wish_lists/105243
 
Development environment specifics:
Developed for Arduino 1.65

This code is beerware; if you see me (or any other SparkFun employee) at the local, 
and you've found our code helpful, please buy us a round!

For the official license, please check out the license file included with the library.

Distributed as-is; no warranty is given.
*************************************************************************/

#define button1 A0
#define button2 A1

#include <EEPROM.h>
#include <MicroView.h>

unsigned char count;  // a "char" is 8-bits = one byte It makes the numbers go from 0 to 255

void setup() {


pinMode(button1,INPUT);
digitalWrite(button1,HIGH);
pinMode(button2,INPUT);
digitalWrite(button2,HIGH);
  
count = EEPROM.read(0); //read what was saved at spot 0 and make it equal to count
  
  uView.begin();
  uView.clear(PAGE);		// clear page
  uView.print("Hello Liz!");
  uView.display();
  delay(2000);
  uView.setCursor(0,0);
  uView.print("Let's knit");
  uView.display();
  delay(2000);
  uView.setCursor(0,0);
  uView.print("Ur on row ");
  uView.display();
}

void loop() {

static boolean pressed1 = false;
static long int presstime1 = 0L;
static boolean longpress1 = false;

static boolean pressed2 = false;
static long int presstime2 = 0L;
static boolean longpress2 = false;


if (digitalRead(button1) == 0)
{
  if (!pressed1)
  {
     pressed1 = true;
     presstime1 = millis();
     count++; //add one to the count
     EEPROM.write(0,count); //save it
  }
  else
  if (!longpress1 && (millis() > (presstime1 + 3000)))
  {
    longpress1 = true;
    count = 0; //reset
    EEPROM.write(0,count); //save it
  }
}
else
{
  if (pressed1 && (millis() > presstime1 + 1))
  {
    pressed1 = false;    
    longpress1 = false;
  }
}

  
if (digitalRead(button2) == 0)
{
  if (!pressed2)
  {
     pressed2 = true;
     presstime2 = millis();
     count--;
     EEPROM.write(0,count);
  }
  else
  if (!longpress2 && (millis() > (presstime2 + 3000)))
  {
    longpress2 = true;
    count = 0;
    EEPROM.write(0,count);
  }
}
else
{
  if (pressed2 && (millis() > presstime2 + 1))
  {
    pressed2 = false;    
    longpress2 = false;
  }
}
  
//uView.setCursor(0,10);
//uView.print("   ");
//uView.display();
// I want to add the above to remove orphaned char on the screen, but it makes the number flicker

uView.setCursor(0,10);
uView.print(count);
uView.display();
  
}
