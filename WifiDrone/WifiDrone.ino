#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "ESP32_Router";
const char *password = "12345678";

int PWM[4] = { 200, 200, 200, 200 };

int dP[4] = { 200, 200, 200, 200 };//default PWM

int aP = 20;//add PWM

//pin         RF  RB  LB  LF
int mot[4] = { 10, 10, 10, 10 };

WebServer server(8585);  // 修改端口為8585

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP:");
  Serial.println(IP);
  server.on("/fly", HTTP_GET, handleFLY);

  // 啟動伺服器
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // 處理客戶端的請求
  server.handleClient();
  for (int i = 0; i < 4; i++) {
    analogWrite(mot[i], PWM[i]);
  }
}

// 處理根路由的函數
void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32 Router!");
}

// 處理LF路由的函數
void handleFLY() {
  // 如果是正確的 URL，設置 pin1 為 HIGH
  String url = server.uri();
  url.remove(0, 4);

  int x[4];  // 将数组定义移到 if-else 语句之前

  if (url.substring(0, 2) == "/F") {
    url.remove(0, 2);
    x[0] = default_
    x[1] = add_PWM;
    x[2] = add_PWM;
    x[3] = -add_PWM;
    server.send(200, "text/plain", "前進");
  } else if (url.substring(0, 2) == "/B") {
    url.remove(0, 2);
    x[0] = add_PWM;
    x[1] = -add_PWM;
    x[2] = -add_PWM;
    x[3] = add_PWM;
    server.send(200, "text/plain", "後退");
  } else if (url.substring(0,3) == "/UP") {
    url.remove(0, 3);
    x[0] = +add_PWM;
    x[1] = +add_PWM;
    x[2] = +add_PWM;
    x[3] = +add_PWM;
    server.send(200, "text/plain", "上升");
  }else if (url.substring(0,3) == "/DN") {
    url.remove(0, 3);
    x[0] = add_PWM;
    x[1] = -add_PWM;
    x[2] = -add_PWM;
    x[3] = add_PWM;
    server.send(200, "text/plain", "下降");
  }
  }else{
    server.send(404, "text/plain", "找不到此操作");
    return;
  }
  changePWM(url, x);
}




void changePWM(String url, int n[4]) {
  int x = 1;
  if (url == "/up") {
    x = -1;
  }
  for (int i = 0; i < 4; i++) {
    if (n[i] > 50 || n[i] < -50) {
      server.send(500, "text/plain", "PWM調整過度");
      return;
    } else {
      PWM[i] += n[i] * x;
    }
  }
}