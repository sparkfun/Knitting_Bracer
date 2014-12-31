//	EEPROM SETUP
#include <EEPROM.h>

//	BUTTON CONSTANT SETUP
#define buttonPin 2 // analog input pin to use as a digital input
#define debounce 200 // ms debounce period to prevent flickering when pressing or releasing the button
#define holdTime 2000 // ms hold period: how long to wait for press+hold event

//	BUTTON VARIABLE SETUP
int buttonVal = 0; // value read from button
int buttonLast = 0; // buffered value of the button's previous state
long btnDnTime; // time the button was pressed down
long btnUpTime; // time the button was released
boolean ignoreUp = false; // whether to ignore the button release because the click+hold was triggered

//	BUTTON-BASED ACTION VARIABLE SETUP
int CurrentAction = 0;

//	LED BEHAVIORAL LOOP SETUP
int TotalLEDs = 10;
int LEDAssignmentsChart[] = { 10, 11, 12, 13, 3, 4, 5, 6, 7, 8 };
int LEDAssignmentsNumeric[] = { 8, 7, 6, 5, 4, 3, 13, 12, 11, 10 };

// int PatternRows = TYPE_ROW_NUMBER_HERE;
// CHANGE THIS NUMBER TO THE NUMBER OF ROWS IN YOUR PATTERN!
int PatternRows = 16;


//	KNITTING PATTERN ARRAY SETUP
int CurrentRow;
int LEDsAffected = 0;
int LEDAction;
int CurrentLoop = 0;
int TotalDigits = 0;
int DigitsPlusOne = 0;
int CurrentDigit = 0;
int DigitCalculation = 0;
int CurrentDigitArray = 0;
int Delay = 0;


//=================================================


void setup()
{
	// Set button input pin
	pinMode(buttonPin, INPUT);
	for (int i; i < TotalLEDs; i++)  {
		pinMode(LEDAssignmentsChart[i], OUTPUT);      
		digitalWrite(LEDAssignmentsChart[i], LOW);
	}

	//	read EEPROM
	CurrentRow = EEPROM.read(0);
	if (CurrentRow < 1 || CurrentRow > 200)
	{
		EEPROM.write(0, 1);
		CurrentRow = 1;
	}
}


//=================================================


void loop()
{
	TotalDigits = Digits(CurrentRow);
	DigitCalculation = CurrentRow;
	int DigitsToPrint[TotalDigits];
	
	if (CurrentRow > 10)
	{
		int ForLoop = TotalDigits-1;
		while (DigitCalculation > 0)
		{
			DigitsToPrint[ForLoop--] = DigitCalculation % 10;
			DigitCalculation /= 10;
		}
	}
	else
	{
		DigitsToPrint[0] = CurrentRow;
	}
	
	CurrentAction = 0;
	//	match EEPROM
	// Read the state of the button
	buttonVal = digitalRead(buttonPin);
	
	// Test for button pressed and store the down time
	if (buttonVal == LOW && buttonLast == HIGH && (millis() - btnUpTime) > long(debounce))
	{
		btnDnTime = millis();
	}
	
	// Test for button release and store the up time
	if (buttonVal == HIGH && buttonLast == LOW && (millis() - btnDnTime) > long(debounce))
	{
		if (ignoreUp == false)
		{
			CurrentAction = 1;
		}
		else
		{
			ignoreUp = false;
		}
		btnUpTime = millis();
	}
	ActionSelect(CurrentAction);
	buttonLast = buttonVal;

	
	if (CurrentLoop > 27)
	{
		CurrentLoop = 0;
		CurrentDigitArray++;
		for (int i = 0; i < TotalLEDs; i++)
		{
			setLED(LEDAssignmentsNumeric[i], LOW);
		}
		delay(500);
	}
	else
	{
		CurrentLoop++;
	}
	
	if (CurrentDigitArray > TotalDigits)
		{	CurrentDigitArray = 0;	}
	
	if (CurrentDigitArray == TotalDigits)
	{
		LEDsAffected = 10;
		LEDAction = LOW;
		Delay = 32;
	}
	else
	{
		LEDsAffected = DigitsToPrint[CurrentDigitArray];
		LEDAction = HIGH;
		Delay = 100;
	}	
}

//=================================================
// Events to trigger by click and press+hold

void ActionSelect(int ActionSelection)
{
	if (ActionSelection == 1)
		clickEvent();
	else if (ActionSelection == 2)
		holdEvent();
	else
		standardEvent();
}

void standardEvent()
{
	for (int i = 0; i < TotalLEDs; i++)
	{
		setLED(LEDAssignmentsNumeric[i], LOW);
	}
	for (int i = 0; i < LEDsAffected; i = i++)
	{
		setLED(LEDAssignmentsNumeric[i], LEDAction);
	}
	delay(Delay);
}

void clickEvent()
{
	CurrentRow++;
	if (CurrentRow > PatternRows)
		{	CurrentRow = 1;	}
	EEPROM.write(0, CurrentRow);
	DisplayRowNumber(CurrentRow);
}

void holdEvent()
{
	int buttonState = digitalRead(buttonPin);
	// check if the pushbutton is pressed.
	// if it is, the buttonState is HIGH:
	while (buttonState == LOW)
	{     
		// DisplayRowNumber(CurrentRow);
 		if (buttonState != LOW)
 			{	break;	}
	}
}

void DisplayRowNumber(int CurrentRowNumber)
{
	int TotalDigits = Digits(CurrentRowNumber);
	int CurrentDigit;
	int DigitCalculation = ReverseDigits(CurrentRowNumber);
	int DigitsToPrint[TotalDigits];
	int CurrentLoop;

	for (int i = 0; i < TotalLEDs; i++)
	{
		setLED(LEDAssignmentsNumeric[i], LOW);
	}
	delay(2000);
	
	if (CurrentRowNumber > 10)
	{
		for (int i = 0; i < TotalDigits; i = i++)
		{
			CurrentDigit = DigitCalculation % 10;
			DigitCalculation = DigitCalculation / 10;
			DisplayRowDigit(CurrentDigit);
		}
	}
	else
	{
		DigitsToPrint[0] = CurrentRowNumber;
		DisplayRowDigit(CurrentRowNumber);
	}

	for (int i = TotalDigits; i > -1; i--)
	{
		CurrentLoop = DigitsToPrint[i];
		if (CurrentLoop == 0)
			{	CurrentLoop = 10;	}
	}
	for (int i = 0; i < TotalLEDs; i++)
	{
		setLED(LEDAssignmentsNumeric[i], LOW);
	}
	delay(650);
}

int DisplayRowDigit(int CurrentDigit)
{
	for (int i = 0; i < CurrentDigit; i = i++)
	{
		setLED(LEDAssignmentsNumeric[i], HIGH);
	}
	delay(2500);
	for (int i = 0; i < TotalLEDs; i++)
	{
		setLED(LEDAssignmentsNumeric[i], LOW);
	}
	delay(300);
}

int Digits(int CurrentRowNumber)
{
	return floor(log10(CurrentRowNumber)) + 1;
}

int ReverseDigits(int CurrentRowNumber)
{
	int ReverseRowNumber = 0;
	while(CurrentRowNumber>0) {
			ReverseRowNumber += CurrentRowNumber-((CurrentRowNumber/10)*10);
			CurrentRowNumber /= 10;
			if (CurrentRowNumber>0) {
					ReverseRowNumber *= 10;
			}
	}
	return ReverseRowNumber;
}

void setLED(int LED, int Brightness)
{
	digitalWrite(LED, Brightness);
}

void blinkLED(int LED, int Brightness, int Timer)
{
	analogWrite(LED, Brightness);
	delay(Timer);
}
