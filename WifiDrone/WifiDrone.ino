#include <WiFi.h>
 
const char* ssid = "WifiXX";請輸入給你的編號
const char* password = "WifiDrone8585";

// Setting Static IP.
        IPAddress local_IP(192, 168, 1, 1XX);//請輸入給你的編號
        IPAddress gateway(192, 168, 1, 1);
        IPAddress subnet(255, 255, 255, 0); 
        IPAddress primaryDNS(8, 8, 8, 8); //可選
        IPAddress secondaryDNS(8, 8, 4, 4); //可選

WiFiServer server(80); // Port 80

int wait30 = 30000; // 連線丟失時的等待時間 單位ms(30000ms=30s)
//左前馬達
int mtFLa = ;
int mtFLb = ;
int mtFLp = ;
//右前馬達
int mtFRa = ;
int mtFRb = ;
int mtFRp = ;
//左後馬達
int mtBLa = ;
int mtBLb = ;
int mtBLp = ;
//右後馬達
int mtBRa = ;
int mtBRb = ;
int mtBRp = ;
#define FLconst(5);
#define FRconst(5);
#define BLconst(5);
#define BRconst(5);
#define FLvar(1);
#define FRvar(1);
#define BLvar(1);
#define BRvar(1);
void op(String);
void setup(){
	pinMode(mtFLa , OUTPUT);
  pinMode(mtFLb , OUTPUT);
  pinMode(mtFRa , OUTPUT);
  pinMode(mtFRb , OUTPUT);
  pinMode(mtBLa , OUTPUT);
  pinMode(mtBLb , OUTPUT);
  pinMode(mtBRa , OUTPUT);
  pinMode(mtBRb , OUTPUT);
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
void op(String OP){
  switch(OP){
    case "F":
      break;
    case "B":
      break;
    case "L":
      break;
    case "R":
      break;
    case "FL":
      break;
    case "FR":
      break;
    case "BL":
      break;
    case "BR":
      break;
    case "UP":
      break;
    case "DN":
      break;
    case "LRo":
      break;
    case "RRo":
      break;
    case "S":
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
  Serial.println(req);
  if (req.indexOf("on12") != -1) {digitalWrite(LED12, HIGH);}
  if (req.indexOf("off12") != -1){digitalWrite(LED12, LOW);}
  if (req.indexOf("on14") != -1) {digitalWrite(LED14, HIGH);}
  if (req.indexOf("off14") != -1){digitalWrite(LED14, LOW);}
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Comillas importantes.
  client.println(estado); //  Return status.

  client.flush();
  client.stop();
  Serial.println("Client disconnected.");
}
