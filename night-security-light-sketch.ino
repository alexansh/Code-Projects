#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "your ssid";
const char* password = "your password";

// Discord webhook URL
const char* webhookUrl = "discord webhook url goes here";

// Pin definitions
const int ledPin = D1;        // Night light
const int buzzerPin = D2;     // Buzzer
const int ldrDay = A0;        // Day/night LDR
const int ldrLaser = A0;      // Laser LDR (if you use separate ADC, adjust accordingly)
const int laserPin = D3;      // Laser diode control
const int resetButton = D4;   // Manual reset button

// Thresholds (tune these based on your readings)
const int dayThreshold = 700;    // Below this = Night
const int laserThreshold = 600;  // Above this = Laser tripped

bool alertTriggered = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
  
  digitalWrite(laserPin, HIGH);  // Keep laser ON continuously

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
}

void loop() {
  int dayValue = analogRead(ldrDay);
  int laserValue = analogRead(ldrLaser);

  bool isNight = (dayValue < dayThreshold);
  bool laserBroken = (laserValue > laserThreshold);

  // Print for debugging
  Serial.print("Day LDR: "); Serial.print(dayValue);
  Serial.print(isNight ? " (Night)" : " (Day)");
  Serial.print(" | Laser LDR: "); Serial.print(laserValue);
  Serial.println(laserBroken ? " (TRIPPED)" : " (OK)");

  if (digitalRead(resetButton) == LOW) {
    alertTriggered = false;
    noTone(buzzerPin);
    Serial.println("🔁 System Reset!");
    delay(1000);
  }

  if (isNight) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(laserPin, HIGH);

    if (laserBroken && !alertTriggered) {
      alertTriggered = true;
      tone(buzzerPin, 1000);
      Serial.println("🚨 ALERT: Laser beam broken!");
      sendDiscordAlert("🚨 ALERT: Laser beam broken! Intruder detected!");
    }

    if (!laserBroken && !alertTriggered) {
      noTone(buzzerPin);
    }
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(laserPin, LOW);
    noTone(buzzerPin);
  }

  delay(500);
}

void sendDiscordAlert(String message) {
  WiFiClient client;
  HTTPClient http;

  String webhookUrl = "disord webhook url goes here"; 

  http.begin(client, webhookUrl);

  http.addHeader("Content-Type", "application/json");

  String payload = "{\"content\":\"" + message + "\"}";
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.println("✅ Discord Alert Sent Successfully!");
    Serial.print("Response Code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println("❌ Failed to send Discord alert.");
    Serial.print("Error: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
