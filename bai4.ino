#include <Leanbot.h>

const int maxVelocity = 2000;            // Tốc độ tối đa của mỗi bánh xe
const int minVelocity = 1000;            // Tốc độ tối thiểu của mỗi bánh xe
int hasMoved = 0;

void setup() {
    Leanbot.begin();                       // Khởi tạo Leanbot
}

void loop() {
    // Đọc giá trị từ cảm biến IR
    int leftSensorValue = LbIRArray.read(ir6L);
    int rightSensorValue = LbIRArray.read(ir7R);

    // Tính toán lái
    int steeringDiff = rightSensorValue - leftSensorValue;

    if (steeringDiff > 0) {
      // Re phai
      LbMotion.runLR(maxVelocity, minVelocity);
      hasMoved = 1;
    } else {
      if (steeringDiff > -300) {
        // Di thang
        LbMotion.runLR(maxVelocity, maxVelocity);
      }
      else {
        // Di phai
         LbMotion.runLR(minVelocity, maxVelocity);
      }
    }

    if ((hasMoved == 1) and (steeringDiff == 0)) {
      LbMotion.runLR(maxVelocity, maxVelocity);
      LbMotion.waitDistanceMm(100);
      while(1) {}
    }

    // Lặp lại
    LbDelay(200); // Giữ chạy trong 50ms
}