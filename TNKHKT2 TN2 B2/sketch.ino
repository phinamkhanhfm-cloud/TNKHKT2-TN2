#include <Arduino.h>

#define LED_PIN 2
#define TIME_TO_SLEEP 10 // Ngủ 10 giây

// GIỮ qua deep sleep (vùng nhớ RTC)
RTC_DATA_ATTR int soLanThuc = 0; 

// MẤT qua deep sleep (RAM thường)[cite: 15]
int demThuong = 0;               

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  delay(500);

  soLanThuc++;  // Tăng biến RTC[cite: 15]
  demThuong++;  // Tăng biến thường[cite: 15]

  Serial.println("\n================================");
  Serial.print("So lan thuc (RTC_DATA_ATTR): ");
  Serial.println(soLanThuc);
  Serial.print("Dem thuong (RAM thuong): ");
  Serial.println(demThuong);
  Serial.println("================================");

  // Nháy LED báo hiệu thức dậy
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  // Cấu hình đánh thức sau 10s và bắt đầu Deep Sleep[cite: 15]
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000ULL);[cite: 15]
  Serial.println("Bat dau Deep Sleep 10s...");
  Serial.flush();
  esp_deep_sleep_start();[cite: 15]
}

void loop() {
  // Deep sleep khi thức dậy sẽ khởi động lại từ setup(), không vào loop()[cite: 16, 17]
}