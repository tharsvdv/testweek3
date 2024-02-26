// lcd gaat aan maar laat de tekst niet zien. de temperatuur werkt op beide maar de LM335 zit veel te hoog
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BMP280_ADDRESS 0x76
#define LM335_PIN A0

Adafruit_BMP280 bmp;

float temperatureC;
float temperatureK;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("Could not find BMP280 sensor, check wiring!");
    while (1)
      ;
    lcd.init();
    lcd.setBacklight((uint8_t)1);
  }
}

void loop() {
  float bmpTemperature = bmp.readTemperature();
  float lm335Voltage = readLM335Voltage();
  float lm335TemperatureK = lm335Voltage / 10;
  float lm335TemperatureC = lm335TemperatureK;

  Serial.print("BMP280: ");
  Serial.print(bmpTemperature);
  Serial.println(" °C");
  lcd.setCursor(0, 0);
  lcd.print(bmpTemperature);

  Serial.print("LM335: ");
  Serial.print(readLM335Voltage());
  Serial.println(" °C");
  lcd.setCursor(0, 1);
  lcd.print(readLM335Voltage());

  delay(500);
}

float readLM335Voltage() {
  int rawValue = analogRead(LM335_PIN);
  float voltage = (rawValue * 5000) / 1024;



  temperatureK = voltage / 10;
  temperatureC = temperatureK - 273;

  return temperatureC;
}