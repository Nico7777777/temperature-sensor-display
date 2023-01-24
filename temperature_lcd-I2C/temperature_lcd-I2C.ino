#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27,16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float tempCelsius, tempFarenheit;  // the 2 temperature values
const int tempPin = 5;  // the analog pin reading from DHT-11. It holds values within the range of 0-255, thus it must be capable of PWD
DHT dht(tempPin, DHT11);
byte degree[] = {
  B01110,   // this is a grid
  B01010,   // with 5 columns
  B01110,   // and 8 rows, 
  B00000,   // accordingly to
  B00000,   // my Hitachi LCD
  B00000,
  B00000,
  B00000,
};

void setup()
{
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.createChar(0, degree);
  lcd.backlight();
  lcd.setCursor(1,1);
}

void print_temp(float t, char type){
  lcd.print(t, 1); //the integer argument means we only print 1 figure after the decimal point
  lcd.write(0);
  lcd.print(type);
}
void loop()
{ 
  tempCelsius = dht.readTemperature();
  tempFarenheit = dht.readTemperature(true);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temperature = ");
  lcd.setCursor(0, 1);
  print_temp(tempCelsius, 'C');
  lcd.print(" / ");
  print_temp(tempFarenheit, 'F');
  delay(2000);
}
