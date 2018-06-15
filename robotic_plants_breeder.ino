#include "ESP8266WiFi.h"

int plants[4] = {A0};//, A1, A2, A3};
int relays[4] = {1};//, 2, 3, 4};

int waterLimitValue = 800;
int wateringValue = 10 * 1000;

void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.begin(115200);
    
    for (int i=0; i<1; i++) {
        pinMode(plants[i], INPUT);
    }
    Serial.println("Setup done");
    wifiConnection();
}

void loop() {
    for (int i=0; i<1; i++) {
        checkWater(plants[i], i+1);
    }
    delay(5000);
}

void checkWater(int plant, int plant_number) {
    int sensorValue = analogRead(plant);
    Serial.print("Plant number : ");
    Serial.println(plant_number);
    Serial.println(sensorValue);
    if (sensorValue < waterLimitValue) {
        Serial.println("Plant water OK.");
    } else {
        Serial.println("Plant thirsty, watering...");
        digitalWrite(relays[plant_number], HIGH);
        delay(wateringValue);
        digitalWrite(relays[plant_number], LOW);
    }
}

void wifiConnection() {
    Serial.println("WIFI Scan start...");
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("No networks found.");
    } else {
        Serial.print(n);
        Serial.println(" networks found.");
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
}

