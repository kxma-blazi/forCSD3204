6.2
#define BLYNK_TEMPLATE_ID "TMPL6OOuJbH45" 
#define BLYNK_TEMPLATE_NAME "controlLED" 
#define BLYNK_AUTH_TOKEN "aU94763U50PhWtw_UEYl2qAznNbbkBHO" 

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h> // เพิ่มบรรทัดนี้หลังจากติดตั้งไลบรารีแล้ว 

// Wi-Fi Credentials
char ssid[] = "Benzti";
char pass[] = "123456789A";

// กำหนดขาเชื่อมต่อ
#define LED_PIN 19
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// ฟังก์ชันอ่านค่าจากเซ็นเซอร์ DHT11 และส่งไปที่ Blynk
void sendDHTData() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C, Humidity: ");
    Serial.print(h);
    Serial.println(" %RH");

    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
}

void setup() {
    Serial.begin(115200);
    dht.begin();

    // กำหนดให้พิน LED เป็น Output
    pinMode(LED_PIN, OUTPUT);

    // เริ่มต้นการเชื่อมต่อ Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    Serial.println("Connecting to Blynk...");

    // ตั้งเวลาส่งค่าจากเซ็นเซอร์ทุก ๆ 2 วินาที
    timer.setInterval(2000L, sendDHTData);
}

void loop() {
    Blynk.run();
    timer.run();
}

// ฟังก์ชันควบคุม LED ผ่าน Virtual Pin V0
BLYNK_WRITE(V0) {
    int pinValue = param.asInt(); // รับค่าจากแอป (0 = OFF, 1 = ON)
    digitalWrite(LED_PIN, pinValue); // ควบคุมพิน LED
}
