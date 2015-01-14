#include <LiquidCrystal.h>

const int button1Pin = A1;  // pushbutton 1 pin
const int button2Pin = A2;  // pushbutton 2 pin
const int lcd =  13;    // LCD pin

int count;

voidsetup(){
// Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);  
   
   lcd.begin(16, 2);
   lcd.print("Happy Knitting, Liz!");
   
_setValue(counter)
}

voidloop(){

_checkButtonState();
_displayValue();

}
/**
* Button processing. Ideally button should take care of powering up/down, resetting and increasing the counter value.
*/
void _checkButtonState() {
  byte buttonState = digitalRead(BUTTON_PIN);

  if( buttonState == HIGH ) { // Button is pressed
    if( buttonLastState != buttonState ) { // This is the start of "pressed" condition, store the time of event
      buttonDownTimestamp = millis();
    } else { // Button is pressed for some time now
      if(powerMode == PMODE_NORMAL) {
        buttonDownDuration = millis() - buttonDownTimestamp;
      
        if(buttonDownDuration >= TIME_UNTIL_POWER_CYCLE*1000) { // Super-looooong press, go to stand-by while the button is still pressed
          if(powerState == ON) {
              powerState = OFF;
          } else {
            powerState = ON;
          }
          
          powerMode = PMODE_SWITCHING;
          buttonDownDuration = buttonDownTimestamp = 0;
          return; 
        } else if(powerState == ON && buttonDownDuration >= TIME_UNTIL_RESET*1000) { // Long press, reset the counter
          counter = 0;
          _setValue(counter);
        }
      }
    }
  } else {
    if( buttonLastState != buttonState ) { // Button is released
      buttonDownDuration = millis() - buttonDownTimestamp;
      if( powerState == ON ) {
        if(buttonDownDuration < TIME_UNTIL_RESET*1000) { // Short press, increase counter value
          counter++;
          _setValue(counter);
        }
        
        buttonDownDuration = buttonDownTimestamp = 0;
      }
      powerMode = PMODE_NORMAL;
    }
  }

  buttonLastState = buttonState;
}
