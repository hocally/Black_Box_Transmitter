/*
1 - GND
2 - VCC 3.3V !!! NOT 5V
3 - CE to Arduino pin 7
4 - CSN to Arduino pin 8
5 - SCK to Arduino pin 13
6 - MOSI to Arduino pin 11
7 - MISO to Arduino pin 12
8 - UNUSED
/*-----( Import needed libraries )-----*/
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
/*-----( Declare objects )-----*/
// (Create an instance of a radio, specifying the CE and CS pins. )
RF24 myRadio(7, 8); // "myRadio" is the identifier you will use in following methods
					/*-----( Declare Variables )-----*/
byte addresses[][6] = { "1Node" }; // Create address for 1 pipe.
int dataTransmitted;  // Data that will be Transmitted from the transmitter
int accelXPin = A0;
int accelYPin = A1;
int accelZPin = A2;
int voltagePin = A3;
int accelXVal;
int accelYVal;
int accelZVal;
int voltageVal;
String data;

void setup()   /****** SETUP: RUNS ONCE ******/
{
	// Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
	Serial.begin(115200);
	myRadio.begin();  // Start up the physical nRF24L01 Radio
	myRadio.setChannel(108);  // Above most Wifi Channels
	myRadio.setPALevel(RF24_PA_MAX);
	myRadio.openWritingPipe(addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
	pinMode(accelXPin, INPUT);
	pinMode(accelYPin, INPUT);
	pinMode(accelZPin, INPUT);
	pinMode(voltagePin, INPUT);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
	accelXVal = analogRead(accelXPin);
	accelYVal = analogRead(accelYPin);
	accelZVal = analogRead(accelZPin);
	voltageVal = analogRead(voltagePin);
	voltageVal = map(voltageVal, 0, 1023, 0, 15);

	data = "|" +accelXVal;
	data += "|" + accelYVal;
	data += "|" + accelZVal;
	data += "|" + voltageVal;
	myRadio.write(&data, sizeof(data)); //  Transmit the data
}//--(end main loop )---