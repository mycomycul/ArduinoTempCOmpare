/*


  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)



*/
// include the library code:
#include <LiquidCrystal.h>

/*TODO Update temperature calculation to based off 1023 to eliminate getVoltage()

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
bool Light = false;
long tempInside, tempOutside;

bool WarmerInside = true;
bool SwapAlert = false;
unsigned long AlertPeriod = 60000;
unsigned long AlertTime;
int BrightnessIncrementor = 5

    void
    setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Calibrating");
    delay(1500);

    //Setup the LCD pin and turn to off
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    //Setup Button
    pinMode(button, INPUT_PULLUP);
}

void loop()
{
    chkCelsiusBtn();
    chkTemp();
    checkForTempSwap();
    updateLCD();
    while (SwapAlert == true)
    {
        alertTempSwap();
    }
}
void chkTemp()
{
    //Get the first sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin1);
    tempInside = calculateTemperature(voltage);
    //Get the second sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin2);
    tempOutside = calculateTemperature(voltage);
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
checkForTempSwap()
{
    bool tempSwapCheck = WarmerInside;
    if (tempInside < tempOutside)
    {
        WarmerInside = false;
    }
    else
    {
        WarmerInside = true;
    }

    if (tmpSwapCheck != WarmerInside)
    {
        SwapAlert = true;
        AlertTime = millis();
    }
}
alertTempSwap()
{
    long currentTime = millis();
    //Check how long the alert has run
    if (currentTime - AlertTime <= AlertPeriod)
    {
        LedBrightness = LedBrightness + BrightnessIncrementor;
        analogWrite(ledPin, LedBrightness);
        //Reverse Fade
        if (LedBrightness >= 250 || LedBrightness <= 5)
        {
            BrightnessIncrementor = !BrightnessIncrementor;
        }
    }
    //Turn off alert if alertperiod has passed
    else{
        SwapAlert = false;
    }
}

void updateLCD()
{
    lcd.clear();
    // set the cursor to column 0, line 1
    lcd.setCursor(0, 0);
    String s = String(tempInside, 1);
    // print temperature
    lcd.print("In:" + String(tempInside, 1));
    lcd.setCursor(0, 1);
    lcd.print("Out:" + String(tempOutside, 1));
}

void chkCelsiusBtn()
{
    int sensorVal = digitalRead(2);
    if (sensorVal == LOW)
        ;
    {
        Celsius = !Celsius;
    }
}
