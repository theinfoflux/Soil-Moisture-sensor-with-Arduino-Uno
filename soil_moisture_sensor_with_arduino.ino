#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define sensorpin A0
#define buzzer 3
#include "DHT.h"
int DHTPIN= 2;
int dry = 595; // value for dry sensor
int wet = 239; // value for wet sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float temp; //to store the temperature value
float hum; // to store the humidity value

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);
  pinMode(sensorpin,INPUT);
  pinMode(buzzer,OUTPUT);
  dht.begin();          //Begins to receive Temperature and humidity values.  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  delay(1000);
}

void loop() {
  // Read the Analog Input
  int moisturevalue = analogRead(sensorpin);
  int pcentmoisture=map(moisturevalue, wet, dry, 100, 0);
  temp = dht.readTemperature();
 hum = dht.readHumidity();
 Serial.print("temperature = ");
 Serial.println(temp);
 Serial.print("humidity = ");
 Serial.println(hum);
  // Print the value to the serial monitor
  Serial.print("Analog output: ");
  Serial.println(moisturevalue);
 if( pcentmoisture<15)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  } 
  
 display.clearDisplay();
 display.setCursor(10,0);  
 display.setTextSize(2);
 display.setTextColor(WHITE);
 display.print("MV:"+String(pcentmoisture)+"%");
 display.setCursor(10,23);
 display.setTextSize(2);
 display.print("T:"+String(temp));
 display.print((char)247);
 display.print("C");
 display.setCursor(10,45);
 display.setTextSize(2);
 display.print("H:"+String(hum));
 display.display();    
 delay(500);
}
