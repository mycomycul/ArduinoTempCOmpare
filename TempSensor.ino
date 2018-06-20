#include "LiquidCrystal.h"

//Thermometer pin #s. Set these to analog pins attached to sensors
const int tempPin1 = 0;
const int tempPin2 = 1
//LCD pin #s
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Environment Variables
bool Celsius = false, Light = false;

void setup()
{
lcd.begin(16,2);
lcd.print("Calibrating");
delay(1000);
}

void loop()
{

    float voltage, temperature1, temperature2;
//Get the first sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin1);
    temperature1 = getTemperature(voltage);
//Get the second sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin2);
    temperature2 = getTemperature(voltage);


lcd.print("In: " + String(temperature1,1) + " Out:" + String(temperature2,1));

    delay(5000);
}

    //Global variable Celsius tell getTemperature in what format to out. Celsius = true, fahrenheit = false
float getTemperature(float voltage)
{
    if (Celsius == true)
    {
        return ((voltage - 0.5) * 100.0);
    }
    else
    {
        return ((voltage - 0.5) * 100.0) * (9.0 / 5.0) + 32.0;
    }
}

float getVoltage(int pin)
{

    return (analogRead(pin) * 0.004882814);

    // This equation converts the 0 to 1023 value that analogRead()
    // returns, into a 0.0 to 5.0 value that is the true voltage
    // being read at that pin.
}
