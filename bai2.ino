#include <Leanbot.h>

int SPEED_MAX = 2000;             // Tốc độ tối đa
int SPEED_4   = 0.8 * SPEED_MAX;  // 80% tốc độ
int SPEED_3   = 0.6 * SPEED_MAX;  // 60% tốc độ
int SPEED_2   = 0.4 * SPEED_MAX;  // 40% tốc độ
int SPEED_1   = 0.2 * SPEED_MAX;  // 20% tốc độ
int SPEED_0   = 0.0 * SPEED_MAX;  // Dừng

int hasTurned = 0;

void setup() {
  Leanbot.begin();                // Khởi tạo Leanbot
  Serial.begin(9600);             // Khởi động giao tiếp serial
}

void chay() {
  byte line = LbIRLine.read(100);  // Đọc giá trị từ cảm biến
  Serial.println(line);           // Gửi kết quả đến máy tính

  switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;

    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_4);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_3, SPEED_1);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_4, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_4, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;
    
    case 0b1111:
      LbMotion.runLR(SPEED_1, SPEED_3);
      break;

    case 0b1110:
      if (hasTurned == 0) {
        quay90Do(false);
      }
      hasTurned = 1;
      break;
  }
  LbDelay(200);
}

void quay90Do(boolean clockwise) {
  if (clockwise) {
    LbMotion.runLR(SPEED_2, -SPEED_2);  // Quay tại chỗ theo chiều kim đồng hồ
  } else {
    LbMotion.runLR(-SPEED_2, SPEED_2);  // Quay tại chỗ ngược chiều kim đồng hồ
  }
  LbMotion.waitRotationDeg(90);    // Quay 90 độ
  LbMotion.runLR(0, 0);             // Dừng lại sau khi quay
}

void loop() {
  chay(); // Gọi hàm chay liên tục để theo dõi đường đi
}
