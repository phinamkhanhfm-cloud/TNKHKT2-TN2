#include <Arduino.h>

#define LED1 2
#define ADC 34

unsigned long lanTruocLed = 0;
unsigned long lanTruocAdc = 0;
unsigned long lanTruocHeart = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  // 1. Chớp/tắt LED1 mỗi 500ms
  if (now - lanTruocLed >= 500) {
    lanTruocLed = now;
    digitalWrite(LED1, !digitalRead(LED1)); /* toggle LED1 */
  }

  // 2. Đọc biến trở (ADC) mỗi 2000ms
  if (now - lanTruocAdc >= 2000) {
    lanTruocAdc = now;
    int tho = analogRead(ADC); /* doc ADC */
    Serial.print("Giá trị ADC: ");
    Serial.println(tho);
  }

  // 3. In heartbeat mỗi 5000ms
  if (now - lanTruocHeart >= 5000) {
    lanTruocHeart = now; /* heartbeat */
    Serial.println("heartbeat");
  }
}