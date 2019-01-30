/*


  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * LCD LED pin to 220 resistor to pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * TMP1 VOut pin to A0
 * TMP2 VOut pint to A1
 * BTN Terminal 1 to digital pin 2
 * BTN Terminal 2 to GND
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)


*/
// include the library code:
#include <LiquidCrystal.h>

/*TODO 
Update temperature calculation to based off 1023 to eliminate getVoltage()
Fix alertTempSwap to work with BrightnessIncrementor of 1. To increase fade time consider
    multiplying the LedBrightness by 10 and use for increment but divide when setting pin.
*/

// initialize LCD library for tinkercad
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
const int ledPin = 7;
int LedBrightness = 0;

//Display Pins for Dr.Rob ot
//LiquidCrystal lcd(8,9,4,5,6,7);
//const int ledPin = 10;

//Set temperature probe pins
const int tempPin1 = A0;
const int tempPin2 = A1;

//Set fahrenheit to celsius formatting button pin
const int button = 2;

//Environment Variables
bool Celsius = false;
bool updateDisplay = true;
long tempInside, tempOutside;

bool WarmerInside = true;
bool SwapAlert = false;
unsigned long AlertPeriod = 800;
unsigned long AlertTime;
int BrightnessIncrementor = 1;

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Calibrating");
    //delay(1500);

    //Setup the LCD pin and turn to off
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    //Setup Button
    pinMode(button, INPUT_PULLUP);
}

void loop()
{
    
    updateDisplay = chkCelsiusBtn();
    bool tempChanged = chkTemp();
    if (tempChanged == true)
    {        
        checkForTempSwap();
        updateDisplay = true;
    }
    if (SwapAlert == true)
    {
        alertTempSwap();
    }
    if (updateDisplay == true){
        updateLCD();
    }
}
bool chkTemp()
{
    bool tempsChanged = false;
    //Get sensor values and convert to temperature
    float voltage = getVoltage(tempPin1);    
    long tempTempInside = calculateTemperature(voltage);
    voltage = getVoltage(tempPin2);
    long tempTempOutside = calculateTemperature(voltage);
    //Check if the temperature has changed
    if (tempTempInside != tempInside || tempTempOutside != tempOutside){
        tempsChanged = true;
    }
    tempInside = tempTempInside;
    tempOutside = tempTempOutside;
    return tempsChanged;

}
float getVoltage(int pin)
{
    return (analogRead(pin) * 0.004882814);
}
float calculateTemperature(float voltage)
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

void checkForTempSwap()
{
    bool tempSwapCheck = WarmerInside;
    if (tempInside <= tempOutside)
    {
        WarmerInside = false;
    }
    else
    {
        WarmerInside = true;
    }

    if (tempSwapCheck != WarmerInside)
    {
        SwapAlert = true;
        AlertTime = millis();
    }
}
void alertTempSwap()
{
    long currentTime = millis();
    //Check how long the alert has run
    if (currentTime - AlertTime <= AlertPeriod)
    {
        LedBrightness = LedBrightness + BrightnessIncrementor;
        analogWrite(ledPin, LedBrightness);
        if (LedBrightness >= 255 - abs(BrightnessIncrementor))
        {
            BrightnessIncrementor = -BrightnessIncrementor;
        }
        else if(LedBrightness < abs(BrightnessIncrementor))
        {
          	BrightnessIncrementor = abs(BrightnessIncrementor);
        }
        

        //Reverse Fade
    }
    //Turn off alert if alertperiod has passed
    else
    {
        SwapAlert = false;
        LedBrightness = 0;
        analogWrite(ledPin, LedBrightness);
    }
}

void updateLCD()
{
    char tempType;
    if(Celsius == true){
        tempType = 'C';
    }
    else{
        tempType = 'F';
    }
    lcd.clear();
    // set the cursor to column 0, line 1
    lcd.setCursor(0, 0);
    String s = String(tempInside, 1);
    // print temperature
    lcd.print("In:" + String(tempInside) + tempType);
    lcd.setCursor(0, 1);
    lcd.print("Out:" + String(tempOutside) + tempType);
    updateDisplay = false;
}

bool chkCelsiusBtn()
{
    int sensorVal = digitalRead(2);
    if (sensorVal == LOW)
    {
        Celsius = !Celsius;
        return true;
    }
        return false;
}
