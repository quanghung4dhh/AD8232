#include <Arduino.h>

// --- CẬP NHẬT ĐỊNH NGHĨA CHÂN MỚI ---
const int PIN_ADC_INPUT = 34; // Vẫn giữ GPIO 34 (Analog ADC1_CH6)
const int PIN_LO_PLUS   = 18; // Đổi sang GPIO 18
const int PIN_LO_MINUS  = 19; // Đổi sang GPIO 19

void setup() {
  // Bật Serial tốc độ cao
  Serial.begin(115200);

  // Cấu hình chân Digital Input
  // Lưu ý: AD8232 đẩy mức logic ra (Push-pull), nên ta dùng INPUT thường
  pinMode(PIN_LO_PLUS, INPUT);
  pinMode(PIN_LO_MINUS, INPUT);

  // Cấu hình chân Analog
  pinMode(PIN_ADC_INPUT, INPUT);
  
  delay(100);
}

void loop() {
  // 1. Kiểm tra tuột dây trước
  // Nếu LO+ hoặc LO- lên mức cao -> Dây điện cực bị tuột
  if ((digitalRead(PIN_LO_PLUS) == 1) || (digitalRead(PIN_LO_MINUS) == 1)) {
    Serial.println(0); // Gửi 0 hoặc dấu hiệu để biết đang lỗi
  } 
  else {
    // 2. Đọc giá trị Analog
    // ESP32 ADC: 0 -> 4095 (tương ứng 0 -> 3.3V)
    int adcValue = analogRead(PIN_ADC_INPUT);
    
    // 3. Gửi lên máy tính để vẽ đồ thị
    Serial.println(adcValue);
  }

  // Tốc độ lấy mẫu ~ 100-200Hz là đủ cho ECG cơ bản
  delay(10); 
}