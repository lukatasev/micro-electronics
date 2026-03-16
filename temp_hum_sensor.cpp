#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 20
#define SCL_PIN 21

#define DHTPIN 10
#define DHTTYPE DHT11

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);       
  display.println("Temperature");

  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  // Readingd
  display.setTextSize(2);
  display.setCursor(0, 16);      
  display.print("Temp:");
  display.print(temp, 1);
  display.println("C");

  display.setCursor(0, 40);      
  display.print("Hum:");
  display.print(hum, 1);
  display.println("%");

  display.display();
  delay(2000);
}
