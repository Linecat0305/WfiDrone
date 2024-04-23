#include <WiFi.h>
#include <WebServer.h>

const char ssid[] = "WifiEX";
const char password[] = "WifiDrone8585";

// Setting Static IP.
IPAddress local_IP(192, 168, 1, 120);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);    //可選
IPAddress secondaryDNS(8, 8, 4, 4);  //可選
WebServer server(85);                // 建立一個 WebServer 物件，監聽在 85 port
//一堆定義不用理會
//左前馬達
int mtFLp = 34;
//右前馬達
int mtFRp = 35;
//左後馬達
int mtBLp = 32;
//右後馬達
int mtBRp = 33;
//LED燈腳位
int LEDpin = 13;
//飛行常數
int flyconst 200
int HighPoint = 50;
int LowPoint = -50;
//四軸微調倍率（未調整完畢）
int FLvar = 1.002;
int FRvar = 1.004;
int BLvar = 0.998;
int BRvar = 0.999;
//各軸常數=飛行常數+微調倍率
int FLconst = flyconst*FLvar;
int FRconst = flyconst*FRvar;
int BLconst = flyconst*BLvar;
int BRconst = flyconst*BRvar;
//各軸高位=各軸常數+高位常數*微調倍率
int FLhigh = (FLconst+HighPoint)*FLvar;
int FRhigh = (FRconst+HighPoint)*FRvar;
int BLhigh = (BLconst+HighPoint)*BLvar;
int BRhigh = (BRLconst+HighPoint)*BRvar;
//各軸低位=各軸常數+低位常數-微調倍率
int FLlow = (FLconst+LowPoint)*FLvar;
int FRlow = (FLconst+LowPoint)*FRvar;
int BLlow = (FLconst+LowPoint)*BLvar;
int BRlow = (FLconst+LowPoint)*BRvar;

void setup() {
  pinMode(mtFLp, OUTPUT);
  pinMode(mtFRp, OUTPUT);
  pinMode(mtBLp, OUTPUT);
  pinMode(mtBRp, OUTPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(115200);

  // 設定 ESP32 為 AP 模式
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.softAP(ssid, password);


  IPAddress IP = WiFi.softAPIP();  // 取得 ESP32 AP 的 IP 地址
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // 設定 WebServer 路由
  server.on("/", handleRoot);  // 設定根路徑的處理函式
  server.on("/F", Front);
  server.on("/B", B);
  server.on("/L", L);
  server.on("/R", R);
  server.on("/FL", FL);
  server.on("/FR", FR);
  server.on("/BL", BL);
  server.on("/BR", BackRight);
  server.on("/UP", UP);
  server.on("/DN", DN);
  server.on("/LRo", LRo);
  server.on("/RRo", RRo);
  server.on("/S", S);

  // 開始 WebServer
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // 處理網路請求
}

// 處理根路徑的請求
void handleRoot() {
  String html = "<!DOCTYPE html>";
html+="<html lang=\"zh-TW\">";
html+="<head>";
    html+="<meta charset=\"UTF-8\">";
    html+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html+="<title>Controller</title>";
    html+="<style>";
        html+=".countroller_rows{display: flex;width: 200px;justify-content:space-between;}";
        html+=".countroller_box{margin: 30px;display: flex;flex-direction:column;justify-content:space-between;width: 200px;height: 200px;}";
        html+=".button{width: 60px;height: 60px;}";
        html+=".controller{position: fixed;bottom: 0;width: 100%;display: flex;justify-content:space-between;}";
    html+="</style>";
html+="</head>";
html+="<body>";
    html+="<div style=\"display: flex; justify-content: space-around;\">";
        html+="<button id=\"menu\" onclick=\"fetch(\'http\://192.168.4.1/S\', {method: \'GET\'})\">";
            html+="<p style=\"margin: 0;\">---------</p>";
            html+="<p style=\"margin: 0;\">---------</p>";
            html+="<p style=\"margin: 0;\">---------</p>";
        html+="</button>";
    html+="</div>";
    html+="<div class=\"controller\">";
        html+="<div class=\"countroller_box\" id=\"left-controller\">";
            html+="<div class=\"countroller_rows\">";
                html+="<button id=\"FL\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/FL\', {method: \'GET\'})\">Front-Left</button>";
                html+="<button id=\"F\" class=\"button\"  onclick=\"fetch(\'http\://192.168.4.1/F\', {method: \'GET\'})\">Front</button>";
                html+="<button id=\"FR\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/FR\', {method: \'GET\'})\">Front-Right</button>";
            html+="</div>";
            html+="<div class=\"countroller_rows\">";
                html+="<button id=\"L\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/L\', {method: \'GET\'})\">Left</button>";
                html+="<div class=\"button\"></div>";
                html+="<button id=\"R\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/R\', {method: \'GET\'})\">Right</button>";
            html+="</div>";
            html+="<div class=\"countroller_rows\">";
                html+="<button id=\"BL\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/BL\', {method: \'GET\'})\">back-Left</button>";
                html+="<button id=\"B\" class=\"button\"  onclick=\"fetch(\'http\://192.168.4.1/B\', {method: \'GET\'})\">back</button>";
                html+="<button id=\"BR\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/BR\', {method: \'GET\'})\">back-Right</button>";
            html+="</div>";
        html+="</div>";
        html+="<div class=\"countroller_box\" id=\"right-controller\">";
            html+="<div class=\"countroller_rows\">";
                html+="<div class=\"button\"></div>";
                html+="<button id=\"UP\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/UP\', {method: \'GET\'})\">Up</button>";
                html+="<div class=\"button\"></div>";
            html+="</div>";
            html+="<div class=\"countroller_rows\">";
                html+="<button id=\"LRo\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/LRo\', {method: \'GET\'})\">Left-turn</button>";
                html+="<div class=\"button\"></div>";
                html+="<button id=\"RRo\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/RRo\', {method: \'GET\'})\">Right-turn</button>";
            html+="</div>";
            html+="<div class=\"countroller_rows\">";
                html+="<div class=\"button\"></div>";
                html+="<button id=\"DN\" class=\"button\" onclick=\"fetch(\'http\://192.168.4.1/DN\', {method: \'GET\'})\">Down</button>";
                html+="<div class=\"button\"></div>";
            html+="</div>";
        html+="</div>";
    html+="</div>";
html+="</body>";
html+="</html>";
  server.send(200, "text/html", html);
}
void Front() {
  analogWrite(mtFLp, FLconst);
  analogWrite(mtFRp, FRconst);
  analogWrite(mtBLp, BLhigh);
  analogWrite(mtBRp, BRhigh);
  Serial.println("F");
  digitalWrite(13,HIGH);
  delay(1000);
}
void B() {
  analogWrite(mtFLp, FLhigh);
  analogWrite(mtFRp, FRhigh);
  analogWrite(mtBLp, BLconst);
  analogWrite(mtBRp, BRconst);
  Serial.println("B");
}
void L() {
  analogWrite(mtFLp, FLconst);
  analogWrite(mtFRp, FRhigh);
  analogWrite(mtBLp, BLconst);
  analogWrite(mtBRp, BRhigh);
  Serial.println("L");
}
void R() {
  analogWrite(mtFLp, FLhigh);
  analogWrite(mtFRp, FRconst);
  analogWrite(mtBLp, BLhigh);
  analogWrite(mtBRp, BRconst);
  Serial.println("R");
}
void FL() {
  analogWrite(mtFLp, FLlow);
  analogWrite(mtFRp, FRconst);
  analogWrite(mtBLp, BLconst);
  analogWrite(mtBRp, BRhigh);
}
void FR() {
  analogWrite(mtFLp, FLconst);
  analogWrite(mtFRp, FRlow);
  analogWrite(mtBLp, BLhigh);
  analogWrite(mtBRp, BRconst);
}
void BL() {
  analogWrite(mtFLp, FLconst);
  analogWrite(mtFRp, FRhigh);
  analogWrite(mtBLp, BLlow);
  analogWrite(mtBRp, BRconst);
}
void BackRight() {
  analogWrite(mtFLp, FLhigh);
  analogWrite(mtFRp, FRconst);
  analogWrite(mtBLp, BLconst);
  analogWrite(mtBRp, BRlow);
}
void UP() {
  analogWrite(mtFLp, FLhigh);
  analogWrite(mtFRp, FRhigh);
  analogWrite(mtBLp, BLhigh);
  analogWrite(mtBRp, BRhigh);
}
void DN() {
  analogWrite(mtFLp, FLlow);
  analogWrite(mtFRp, FRlow);
  analogWrite(mtBLp, BLlow);
  analogWrite(mtBRp, BRl);
}
void LRo() {
  analogWrite(mtFLp, FLlow);
  analogWrite(mtFRp, FRhigh);
  analogWrite(mtBLp, BLhigh);
  analogWrite(mtBRp, BRlow);
}
void RRo() {
  analogWrite(mtFLp, FLhigh);
  analogWrite(mtFRp, FRl);
  analogWrite(mtBLp, BLlow);
  analogWrite(mtBRp, BRhigh);
}
void S() {
  analogWrite(mtFLp, FLconst);
  analogWrite(mtFRp, FRconst);
  analogWrite(mtBLp, BLconst);
  analogWrite(mtBRp, BRconst);
  digitalWrite(13,LOW);
  delay(1000);
}