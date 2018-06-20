

const int temperaturePin = 0;
//Environment Variables
bool Celsius = false, Light = false;

void setup()
{

}


void loop()
{

  float voltage, temperature;



  voltage = getVoltage(temperaturePin);
//Global variable Celsius = true outputs Celsius else output Fahrenheit
temperature = getTemperature(voltage);







  delay(1000); 
}

float getTemperature( float voltage){
    if (Celsius == true){
        return ((voltage - 0.5) * 100.0);
    }
    else{
        return ((voltage - 0.5) * 100.0) * (9.0/5.0) + 32.0;
    }
}


float getVoltage(int pin)
{


  return (analogRead(pin) * 0.004882814);

  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}
