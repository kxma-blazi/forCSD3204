// FIRMWARE CONFIGURATION
#define BLYNK_TEMPLATE_ID "TMPL6MzjsrFyu"
#define BLYNK_TEMPLATE_NAME "SSRU Lab014"
#define BLYNK_AUTH_TOKEN "_ocK6mwEeIuw5daV-2lSPkTQqRihW8Rw"

// Library ของ Blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi Credentials
char ssid[] = "Benzti"; // ชื่อ Wi-Fi ที่ใช้เชื่อม
char pass[] = "123456789A"; // รหัสผ่าน Wi-Fi ที่ใช้เชื่อม

// กำหนดพิน LED
#define LED_PIN 19

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดให้พิน LED เป็น Output
  pinMode(LED_PIN, OUTPUT);

  // เริ่มต้นการเชื่อมต่อ Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Connecting to Blynk...");
}

void loop() {
  // Blynk Run
  Blynk.run();
}

// ฟังก์ชันควบคุม LED ผ่าน Virtual Pin V0
BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // รับค่าจากแอป (0 = OFF, 1 = ON)
  digitalWrite(LED_PIN, pinValue); // ควบคุมพิน LED
}