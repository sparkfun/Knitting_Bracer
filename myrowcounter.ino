#include <MicroView.h>

const int button1Pin = 2;  // pushbutton 1 pin
const int button2Pin = 3;  // pushbutton 2 pin
const int ledPin =  13;    // LED pin

voidsetup(){
// Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);      
}

voidloop(){

int button1State, button2State;  // variables to hold the pushbutton states

  // Since a pushbutton has only two states (pushed or not pushed),
  // we've run them into digital inputs. To read an input, we'll
  // use the digitalRead() function. This function takes one
  // parameter, the pin number, and returns either HIGH (5V)
  // or LOW (GND).

  // Here we'll read the current pushbutton states into
  // two variables:

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  // A == B means "EQUIVALENT". This is true if both sides are the same.
  // A && B means "AND". This is true if both sides are true.
  // A || B means "OR". This is true if either side is true.
  // !A means "NOT". This makes anything after it the opposite (true or false).
  
   if (button1State == LOW)  // if we're pushing button 1

  {
    digitalWrite(ledPin, HIGH);  // turn the LED on
  }
  else
  {
    digitalWrite(ledPin, LOW);  // turn the LED off
  }
  
    if (button2State == LOW)  // if we're pushing button 2

  {
    digitalWrite(ledPin, HIGH);  // turn the LED on
  }
  else
  {
    digitalWrite(ledPin, LOW);  // turn the LED off
}
