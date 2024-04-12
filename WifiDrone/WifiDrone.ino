//example file, not for student use.
#include <WiFi.h>

const char* ssid = "WifiXX";//請輸入給你的編號
const char* password = "WifiDrone8585";

// Setting Static IP.
        IPAddress local_IP(192, 168, 1, 120);//請輸入給你的編號
        IPAddress gateway(192, 168, 1, 1);
        IPAddress subnet(255, 255, 255, 0); 
        IPAddress primaryDNS(8, 8, 8, 8); //可選
        IPAddress secondaryDNS(8, 8, 4, 4); //可選

WiFiServer server(80); // Port 80

int wait30 = 30000; // 連線丟失時的等待時間 單位ms(30000ms=30s)
//左前馬達
int mtFLp = ;
//右前馬達
int mtFRp = ;
//左後馬達
int mtBLp = ;
//右後馬達
int mtBRp = ;
//LED燈腳位
int LEDpin = ;
//四軸停滯基數（未調整）
#define FLconst 5
#define FRconst 5
#define BLconst 5
#define BRconst 5
//四軸更動數（未調整）
#define FLvar 1
#define FRvar 1
#define BLvar 1
#define BRvar 1
String OPS[] = {"F","B","L","R","FL","FR","BL","BR","UP","DN","LRo","RRo","S"};
void op(int);
void setup(){
  pinMode(mtFLp , OUTPUT);
  pinMode(mtFRp , OUTPUT);
  pinMode(mtBLp , OUTPUT);
  pinMode(mtBRp , OUTPUT);
  Serial.begin(115200);
// 設定ip
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Error in settings.");
  }

// Connect WiFi net.
  Serial.println();
  Serial.print("Connecting with ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("Connected.");
 
  // Start Web Server.
  server.begin();
  Serial.println("Web Server started.");
 
  // This is IP
  Serial.print("This is IP to connect to the WebServer: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}
void op(int OP){
  switch(OP){
    case 0:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 1:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 2:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 3:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 4:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 5:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 6:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 7:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 8:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 9:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 10:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 11:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
    case 12:
      analogWrite(mtFLp,FLconst);//控制左前馬達
      analogWrite(mtFRp,FRconst);//控制右前馬達
      analogWrite(mtBLp,BLconst);//控制左後馬達
      analogWrite(mtBRp,BRconst);//控制右後馬達
      break;
  }
}
 
void loop() {
// If disconnected, try to reconnect every 30 seconds.
  if ((WiFi.status() != WL_CONNECTED) && (millis() > wait30)) {
    Serial.println("Trying to reconnect WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    wait30 = millis() + 30000;
  } 
  // Check if a client has connected..
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  Serial.print("New client: ");
  Serial.println(client.remoteIP());
  String req = client.readStringUntil('\r');
  String OP = "S";
  Serial.println(req);
  //這裡缺了點東西
    if (req.indexOf(XXX) != -1) {XXX}
  //這裡缺了點東西
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Comillas importantes.

  client.flush();
  client.stop();
  Serial.println("Client disconnected.");
}
