#include <wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // กำหนดความกว้างของจอ OLED
#define SCREEN_HEIGHT 64 // กำหนดความสูงของจอ OLED
#define OLED_RESET -1    // กำหนดขา Reset ของจอ OLED (ใช้ -1 หากไม่ได้ต่อขา Reset)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int adcPin = 34; // กำหนดหมายเลขขาที่จะอ่าน ADC

void setup() {
  Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial

  // เริ่มต้นการทำงานของจอ OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C คือ address I2C ของจอ OLED
    Serial.println(F("SSD1306 allocation failed")); 
    for(;;); // หยุดการทำงานหากจอ OLED ไม่เริ่มต้น
  }
  display.clearDisplay(); // ล้างหน้าจอ OLED
  display.setTextColor(SSD1306_WHITE); // กำหนดสีตัวอักษรเป็นสีขาว
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
}

void loop() {
  int value = analogRead(adcPin); // อ่านค่า Analog จากขา adcPin
  float voltage = (value / 4095.0) * 3.3; // แปลงค่า ADC เป็นแรงดันไฟฟ้า

  // แสดงผลบน Serial Monitor
  Serial.print("ADC value: ");
  Serial.print(value);
  Serial.print(", Voltage: ");
  Serial.println(voltage);

  // แสดงผลบนจอ OLED
  display.clearDisplay(); // ล้างหน้าจอ OLED
  display.setCursor(0, 0); // กำหนดตำแหน่งเริ่มต้นในการแสดงข้อความ
  display.print("ADC: ");
  display.println(value);
  display.setCursor(0, 16); // กำหนดตำแหน่งบรรทัดถัดไป
  display.print("Voltage: ");
  display.print(voltage);
  display.println(" V");
  display.display(); // แสดงผลบนจอ OLED

  delay(1000); // หน่วงเวลา 1 วินาที
}
