//Simple testing program to test that the sensors work by lighting up an LED.


#include<avr/io.h>
#include<util/delay.h>
const int ledPin = 2;
const int tempPin1 = A0;
const int tempPin2 = A1;

bool Celsius = true;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
      float voltage, temperature1, temperature2;
//Get the first sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin1);
    temperature1 = getTemperature(voltage);
//Get the second sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin2);
    temperature2 = getTemperature(voltage);
  
  if(temperature1 > temperature2){
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else{                  // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  }                 // wait for a second
}