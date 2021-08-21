#include <WiFi.h>
#include "Ambient.h"

const char* ssid = "・・・ssid・・・";
const char* password = "・・・パスワード・・・";

unsigned int channelId = 100;
const char* writeKey = "ライトキー";

WiFiClient client;
Ambient ambient;

void setup(){
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client);
}

void loop(){
	int rand;
	rand = random(1000);

    ambient.set(1, rand);                // データーがint型かfloat型であれば、直接セットすることができます。
    ambient.send();

    delay(5000);
}
