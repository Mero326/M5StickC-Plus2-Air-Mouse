#include <M5Unified.h>
#include <BleMouse.h>

BleMouse bleMouse("M5-Air-Remote", "M5Stack", 100);

// Настройки движения из видео: медленный режим.
float sensitivity = 0.87;
float deadzone = 2.0;
float filterK = 0.3;

float lastX = 0, lastY = 0;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Imu.init();

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(CYAN);
  M5.Lcd.println("25% SPEED MODE");

  bleMouse.begin();
}

void loop() {
  M5.update();

  if (bleMouse.isConnected()) {
    float gx, gy, gz;
    M5.Imu.getGyroData(&gx, &gy, &gz);

    // Оси движения из исходного проекта.
    float inputX = -gz;
    float inputY = -gx;

    // Фильтр плавности.
    lastX = lastX + filterK * (inputX - lastX);
    lastY = lastY + filterK * (inputY - lastY);

    int moveX = 0;
    int moveY = 0;

    if (abs(lastX) > deadzone) {
      float valX = (lastX > 0 ? lastX - deadzone : lastX + deadzone);
      moveX = (int)(valX * sensitivity);
    }
    if (abs(lastY) > deadzone) {
      float valY = (lastY > 0 ? lastY - deadzone : lastY + deadzone);
      moveY = (int)(valY * sensitivity);
    }

    // Ограничение перемещения за один цикл.
    moveX = constrain(moveX, -20, 20);
    moveY = constrain(moveY, -20, 20);

    if (moveX != 0 || moveY != 0) {
      bleMouse.move(moveX, moveY);
    }

    // BtnA — левая кнопка мыши; BtnB — правая.
    if (M5.BtnA.wasPressed()) bleMouse.press(MOUSE_LEFT);
    if (M5.BtnA.wasReleased()) bleMouse.release(MOUSE_LEFT);
    if (M5.BtnB.wasPressed()) bleMouse.press(MOUSE_RIGHT);
    if (M5.BtnB.wasReleased()) bleMouse.release(MOUSE_RIGHT);
  }

  delay(10);
}
