#include "LiquidCrystal.h"

//Thermometer pin #s. Set these to analog pins attached to sensors
const int tempPin1 = 0;
const int tempPin2 = 1
//LCD pin #s



//Environment Variables
bool Celsius = false, Light = false;

void setup()
{
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


    delay(1000);
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
