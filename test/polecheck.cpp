#include <Arduino.h>

const int pinLO_Plus = 18;  // Nối với chân LO+ của AD8232
const int pinLO_Minus = 19; // Nối với chân LO- của AD8232
const int pinOutput = 36;   // Nối với chân OUTPUT (VP/A0)

void setup() {
  Serial.begin(115200);
  pinMode(pinLO_Plus, INPUT);
  pinMode(pinLO_Minus, INPUT);
}

void loop() {
  int loPlus = digitalRead(pinLO_Plus);
  int loMinus = digitalRead(pinLO_Minus);

  if (loPlus == 1 || loMinus == 1) {
    Serial.print("CANH BAO: ");
    if (loPlus == 1 && loMinus == 1) {
      Serial.println("Tuot ca hai day RA va LA (hoac chua deo)");
    } else if (loPlus == 1) {
      Serial.println("Tuot dien cuc LA (Left Arm - Ben Trai)");
    } else if (loMinus == 1) {
      Serial.println("Tuot dien cuc RA (Right Arm - Ben Phai)");
    }
  } else {
    // Khi RA và LA đều tốt, ta kiểm tra RL bằng cách đọc giá trị analog
    int sensorValue = analogRead(pinOutput);
    
    // Nếu giá trị bão hòa ở mức thấp nhất (0) hoặc cao nhất (4095)
    // Khả năng cao là mất kết nối RL (Reference)
    
       Serial.println(sensorValue); // In ra tín hiệu để vẽ đồ thị
    }
  delay(100);
}