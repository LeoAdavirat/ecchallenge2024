#include <Leanbot.h>
 
int speed = 1000;                        // Speed of movement
 
void setup() {
  Leanbot.begin();                       // initialize Leanbot
//LbIRLine.doManualCalibration(TB1A);    // touch TB1A to measure black/white level, calibrate line sensors
//LbIRLine.setThreshold(300, 300, 300, 300);    // or measure first and then edit the threshold in the code
}
 
void loop() {
  LbMission.begin();                     // start mission
 
  // follow the black line while still seeing the black line   

  turnNinetyRight();

  LbMotion.runLR(+400, +400);      // let Leanbot go straight
  LbDelay(1500); 

  LbGripper.close();

  LbMotion.runLR(-450, -450);      // let Leanbot go straight
  LbDelay(1500); 

  turnNinetyLeft();
  
  RearfollowLineCarefully();


  LbMotion.waitDistanceMm(410);   


  followLineCarefully();

 
  LbMotion.waitDistanceMm(80); 

  turn180Left();

  
  LbMotion.runLR(+1000, +1000);      // let Leanbot go straight
  LbMotion.waitDistanceMm(75);


  LbGripper.open();

  LbMission.end();                       // stop, finish the mission
}
 
void followLineCarefully() {             // Follow the black line, if you don't see the black line, read it several more times to be sure
  for (int i = 0; i < 30; i++) {         // go up to 30*1mm = 30mm when the black line is not visible
    runFollowLine();
    if ( LbIRLine.isBlackDetected() ) {
      break;
    }
    LbMotion.waitDistanceMm(1);          // go 1mm and then read the sensor again
  }
}
 
void runFollowLine() {
  byte lineValue = LbIRLine.read();      // Read the value of 4 line sensors
  LbIRLine.displayOnRGB(CRGB::DarkCyan); // Display the result on RGB Leds for observation
 
  switch (lineValue) {                   // check the position of the black line relative to Leanbot
    case 0b0100:                         // .o.. - if the black line off to the left
    case 0b1110:                         // ooo.
      LbMotion.runLR(0, +speed);         //        turn left
      break;

    case 0b1100:                         // oo..
    case 0b1000:                         // o...
      LbMotion.runLR(-speed, +speed);    //        spin left
      break;

    case 0b0010:                         // ..o. - if the black line off to the right
    case 0b0111:                         // .ooo
      LbMotion.runLR(+speed, 0);         //        turn right
      break;

    case 0b0011:                         // ..oo
    case 0b0001:                         // ...o
      LbMotion.runLR(+speed, -speed);    //        spin right
      break;

    default:                             // all other cases
      LbMotion.runLR(+speed, +speed);    //        go straight
  }
}

void RearfollowLineCarefully() {             // Follow the black line, if you don't see the black line, read it several more times to be sure
  for (int i = 0; i < 30; i++) {         // go up to 30*1mm = 30mm when the black line is not visible
    rearFollowLine();
    if ( LbIRLine.isBlackDetected() ) {
      break;
    }
    LbMotion.waitDistanceMm(1);          // go 1mm and then read the sensor again
  }
}
void rearFollowLine() {
  byte lineValue = LbIRLine.read();      // Read the value of 4 line sensors
  LbIRLine.displayOnRGB(CRGB::DarkCyan); // Display the result on RGB LEDs for observation

  switch (lineValue) {                   // check the position of the black line relative to Leanbot
    case 0b1100:                         // oo.. - black line on the left
    case 0b1000:                         // o... - far left
      LbMotion.runLR(+speed, -speed);    // spin left (backward)
      break;

    case 0b0011:                         // ..oo - black line on the right
    case 0b0001:                         // ...o - far right
      LbMotion.runLR(-speed, +speed);    // spin right (backward)
      break;

    case 0b0110:                         // .oo. - black line centered
    case 0b0100:                         // .o.. - slightly left
    case 0b0010:                         // ..o. - slightly right
      LbMotion.runLR(-speed, -speed);    // go straight (backward)
      break;

    case 0b1110:                         // ooo. - left intersection
    case 0b0111:                         // .ooo - right intersection
    case 0b1111:                         // oooo - all sensors detect black line (intersection)
      LbMotion.runLR(-speed, -speed);    // go straight (backward) through intersection
      break;

    default:                             // If no black line detected
      LbMotion.runLR(-speed, -speed);    // default to going straight (backward)
      break;
  }
}

void quay90Do(boolean clockwise) {
  if (clockwise) {
    LbMotion.runLR(+speed, -speed);  // Quay tại chỗ theo chiều kim đồng hồ
  } else {
    LbMotion.runLR(-speed, +speed);  // Quay tại chỗ ngược chiều kim đồng hồ
  }
  LbMotion.waitRotationDeg(90);  // Điều chỉnh delay để đạt góc quay 45 độ chính xác
  LbMotion.runLR(0, 0);  // Dừng lại sau khi quay
}

void turnNinetyRight() {
  LbMotion.runRotationDeg(+speed, -speed, +80);  // rotates approximately 90 degrees
  //LbDelay(2000); 
}
void turnNinetyLeft() {
  LbMotion.runRotationDeg(-speed, +speed, +80);  // rotates approximately 90 degrees
  //LbDelay(2000);                                 // delay 2s
}

void turn180Left() {
  LbMotion.runRotationDeg(-speed, +speed, +180);  // rotates approximately 90 degrees
  //LbDelay(2000);                                 // delay 2s
}

void turn180Right() {
  LbMotion.runRotationDeg(+speed, -speed, +180);  // rotates approximately 90 degrees
  //LbDelay(2000);                                 // delay 2s
}