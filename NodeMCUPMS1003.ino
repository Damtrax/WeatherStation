#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <PMS.h>                             //Librería PMS 1003
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int State = LOW;
unsigned long previousMillis = 0;
const long interval = 15000;                  //Máxima velocidad de actualización de datos en thingspeak es 15 segundos


PMS pms(Serial);
PMS::DATA data;

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "RAMIREZ_CA";
const char* password = "10369298";
WiFiClient client;
unsigned long myChannelNumber = 694352;
const char * myWriteAPIKey = "59LWTXPJQIRXWS79";
uint8_t pms2, pms10, pms1;

void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  // Print the IP address
  ThingSpeak.begin(client);

  Wire.begin(D2, D1);
  lcd.begin();
  lcd.backlight();
  
  lcd.home();
  lcd.print("Meteo Santuario");
  delay(2000);
  pms2 = 0;
  pms10 = 0;
  pms1 = 0;
}

void loop() {
  unsigned long currentMillis = millis();
  static boolean data_state = false;

  if (pms.read(data)) {
    lcd.clear();
    pms2 = data.PM_AE_UG_2_5;
    pms10 = data.PM_AE_UG_10_0;
    pms1 = data.PM_AE_UG_1_0;
    lcd.print("PMS 2.5: ");
    lcd.setCursor(9, 0);
    lcd.print(pms2);
    lcd.setCursor(0, 1);
    lcd.print("PMS  10: ");
    lcd.setCursor(9, 1);
    lcd.print(pms10);
    lcd.setCursor(0, 2);
    lcd.print("PMS  1.0: ");
    lcd.setCursor(9, 2);
    lcd.print(pms1);
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (State == LOW) {
      State = HIGH;
    } else {
      State = LOW;
    }

    ThingSpeak.setField(1, pms2);
    ThingSpeak.setField(2, pms10);
    ThingSpeak.setField(3, pms1);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  }

}

ldskfjasldkfjañsldkfjasdfk
