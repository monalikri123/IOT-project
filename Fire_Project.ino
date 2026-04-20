#define BLYNK_TEMPLATE_ID "TMPL3G5ptKY0X"
#define BLYNK_TEMPLATE_NAME "Fire Detector"
#define BLYNK_AUTH_TOKEN "c3aeehnyF-2-dco9cd-upWSgOZ6on-Oz"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Monali's S21+";
char pass[] = "monali01";

#define flamePin D2
#define gasPin A0
#define ledPin D7
#define buzzerPin D5

void setup()
{
  Serial.begin(9600);

  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  int flame = digitalRead(flamePin);
  int gasValue = analogRead(gasPin);

  Blynk.virtualWrite(V1, gasValue);

  // Fire detected
  if (flame == LOW || gasValue > 400)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Blynk.virtualWrite(V0, 1);

    Blynk.logEvent("fire_alert", "Fire detected! Please check immediately.");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(V0, 0);
  }

  delay(200);
}