#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h> // 

// WiFi 配置
const char* ssid = "中国人民银行";
const char* password = "wha16666wha15555";

// HTTP 请求地址
const char* requestUrl = "https://test.wanghaonet.com/yushandevops/embedded/hand?topic=testtopic&group=testtopicg&type=c";

// 引脚定义
const int servoPin1 = 23;
const int servoPin2 = 22;
const int servoPin3 = 21;
const int servoPin4 = 19;

// 角度常量
const int LEFT_ANGLE = 0;
const int RIGHT_ANGLE = 180;

// 轮询间隔（毫秒）
const long INTERVAL_MS = 50;

// ✅ 改为 Servo 类型
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);

  // 初始化舵机
  servo1.attach(servoPin1, 500, 2500); // 可选：指定脉宽范围
  servo2.attach(servoPin2, 500, 2500);
  servo3.attach(servoPin3, 500, 2500);
  servo4.attach(servoPin4, 500, 2500);

  stopServos();

  // 连接 WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void loop() {
  if (millis() - lastTime > INTERVAL_MS) {
    lastTime = millis();

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(requestUrl);
      int httpCode = http.GET();

      if (httpCode > 0) {
        String payload = http.getString();
        int status = payload.toInt();
        Serial.print("Received status: ");
        Serial.println(status);

        handleStatus(status);
      } else {
        Serial.println("Error on HTTP request");
      }
      http.end();
    } else {
      Serial.println("WiFi disconnected");
    }
  }
}

void handleStatus(int status) {
  switch (status) {
    case 1: rotateServo1(servo1, LEFT_ANGLE); break;
    case 2: rotateServo1(servo1, RIGHT_ANGLE); break;
    case 3: rotateServo1(servo2, LEFT_ANGLE); break;
    case 4: rotateServo1(servo2, RIGHT_ANGLE); break;
    case 5: rotateServo1(servo3, LEFT_ANGLE); break;
    case 6: rotateServo1(servo3, RIGHT_ANGLE); break;
    case 7: rotateServo1(servo4, LEFT_ANGLE); break;
    case 8: rotateServo1(servo4, RIGHT_ANGLE); break;
    case 9: stopServos(); break;
    default: Serial.println("Unknown status code"); break;
  }
}

//   一直转
void rotateServo(Servo &servo, int angle) {
  servo.write(angle);
}
//  一步一步转
void rotateServo1(Servo &servo, int angle) {
  servo.write(angle);
  delay(200);
  servo.write(90);
}

void stopServos() {
  rotateServo(servo1, 90);
  rotateServo(servo2, 90);
  rotateServo(servo3, 90);
  rotateServo(servo4, 90);
}
