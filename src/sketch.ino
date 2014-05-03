#include <SerialCommand.h>
#define redPin 9
#define greenPin 10
#define bluePin 11
#define builtin 14
#define buttonUp 3
#define buttonDown 2
#define buttonSelect 8
#define redLed 14
#define greenLed 15
#define blueLed 16
volatile byte r = 0;
volatile byte g = 0;
volatile byte b = 0;
volatile byte token = 0;
byte minDelay = 500;
SerialCommand sCmd;

void serialEvent() {
  sCmd.readSerial();
}

void setup()
{
    Serial.begin(9600);
    sCmd.addCommand("set",	processCommand);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(builtin, OUTPUT);
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    pinMode(buttonSelect, INPUT);
    digitalWrite(buttonUp, HIGH);
    digitalWrite(buttonDown, HIGH);
    digitalWrite(buttonSelect, HIGH);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    attachInterrupt(0, down, LOW);
    attachInterrupt(1, up, LOW);
    setColor(r,g,b);
    digitalWrite((token+14),HIGH);
    delay (minDelay);
    digitalWrite((token+14),LOW);
}

void loop() {
    if (digitalRead(buttonSelect) == LOW) {
	token++;
	digitalWrite(redLed,LOW);
	digitalWrite(greenLed,LOW);
	digitalWrite(blueLed,LOW);
	if (token == 3) {
	  token=0;
	}
	token + 14 = token + 14;
    	digitalWrite((token + 14),HIGH);
        delay (minDelay);
    }
    digitalWrite((token + 14),LOW);
    delay(200);
    setColor(r,g,b);
}

void processCommand () {
  char *arg;
  byte levels[3];
  byte count=0;
  arg = sCmd.next();
  while (arg != NULL || count < 3) {
    Serial.print("Arg received: ");
    Serial.println(arg);
    levels[count]=atoi(arg);
    count++;
    arg = sCmd.next();
  }
  r=levels[0];
  b=levels[1];
  g=levels[2];
  setColor(r,g,b);
}

void setColor(int red, int green, int blue)
{
    analogWrite(redPin, 255-red);
    analogWrite(greenPin, 255-green);
    analogWrite(bluePin, 255-blue);
}

void up () {
    if (token == 0) {
	if (r<255) {
	  r = r + 1;
	}
     } else if ( token == 1 ) {
	if ( b<255) {
	  b = b + 1;
	}
     } else {
	if (g<255) {
	  g = g + 1;
	}
     } 
     delay(minDelay);
}
void down () {
    if (token == 0) {
	if (r>0) {
	  r = r - 1;
	}
     } else if ( token == 1 ) {
	if ( b>0) {
	  b = b - 1;
	}
     } else {
	if (g>0) {
	  g = g - 1;
	}
     } 
     delay(minDelay);
}
