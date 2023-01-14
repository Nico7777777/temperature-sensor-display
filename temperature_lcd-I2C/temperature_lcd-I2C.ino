
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

const int SENSOR_PIN = 13; // Arduino pin connected to DS18B20 sensor's DQ pin

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // I2C address 0x27, 16 column and 2 rows

float tempCelsius;    // temperature in Celsius
float tempFahrenheit; // temperature in Fahrenheit

void setup()
{
  sensors.begin();    // initialize the sensor
  lcd.init();         // initialize the lcd
  lcd.backlight();    // open the backlight 
}

void loop()
{
  sensors.requestTemperatures();             // send the command to get temperatures
  tempCelsius = sensors.getTempCByIndex(0);  // read temperature in Celsius
  tempFahrenheit = tempCelsius * 9 / 5 + 32; // convert Celsius to Fahrenheit

  lcd.clear();
  lcd.setCursor(0, 0);       // start to print at the first row
  lcd.print(tempCelsius);    // print the temperature in Celsius
  lcd.print((char)223);      // print ° character
  lcd.print("C");
  lcd.setCursor(0, 1);       // start to print at the second row
  lcd.print(tempFahrenheit); // print the temperature in Fahrenheit
  lcd.print((char)223);      // print ° character
  lcd.print("F");

  delay(500);
}
