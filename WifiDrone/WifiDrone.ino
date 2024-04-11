//example file, not for student use.
#include <WiFi.h>

const char* ssid = "Wifi20";//請輸入給你的編號
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
int mtFLp = 34;
//右前馬達
int mtFRp = 35;
//左後馬達
int mtBLp = 32;
//右後馬達
int mtBRp = 33;
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
      analogWrite(mtFLp,FLconst);
      analogWrite(mtFRp,FRconst);
      analogWrite(mtBLp,BLconst+BLvar);
      analogWrite(mtBRp,BRconst+BRvar);
      break;
    case 1:
      analogWrite(mtFLp,FLconst+FLvar);
      analogWrite(mtFRp,FRconst+FRvar);
      analogWrite(mtBLp,BLconst);
      analogWrite(mtBRp,BRconst);
      break;
    case 2:
      analogWrite(mtFLp,FLconst);
      analogWrite(mtFRp,FRconst+FRvar);
      analogWrite(mtBLp,BLconst);
      analogWrite(mtBRp,BRconst+BRvar);
      break;
    case 3:
      analogWrite(mtFLp,FLconst+FLvar);
      analogWrite(mtFRp,FRconst);
      analogWrite(mtBLp,BLconst+BLvar);
      analogWrite(mtBRp,BRconst);
      break;
    case 4:
      analogWrite(mtFLp,FLconst-FLvar);
      analogWrite(mtFRp,FRconst);
      analogWrite(mtBLp,BLconst);
      analogWrite(mtBRp,BRconst+BRvar);
      break;
    case 5:
      analogWrite(mtFLp,FLconst);
      analogWrite(mtFRp,FRconst-FRvar);
      analogWrite(mtBLp,BLconst+BLvar);
      analogWrite(mtBRp,BRconst);
      break;
    case 6:
      analogWrite(mtFLp,FLconst);
      analogWrite(mtFRp,FRconst+FRvar);
      analogWrite(mtBLp,BLconst-BLvar);
      analogWrite(mtBRp,BRconst);
      break;
    case 7:
      analogWrite(mtFLp,FLconst+FLvar);
      analogWrite(mtFRp,FRconst);
      analogWrite(mtBLp,BLconst);
      analogWrite(mtBRp,BRconst-BRvar);
      break;
    case 8:
      analogWrite(mtFLp,FLconst+FLvar);
      analogWrite(mtFRp,FRconst+FRvar);
      analogWrite(mtBLp,BLconst+BLvar);
      analogWrite(mtBRp,BRconst+BRvar);
      break;
    case 9:
      analogWrite(mtFLp,FLconst-FLvar);
      analogWrite(mtFRp,FRconst-FRvar);
      analogWrite(mtBLp,BLconst-BLvar);
      analogWrite(mtBRp,BRconst-BRvar);
      break;
    case 10:
      analogWrite(mtFLp,FLconst-FLvar);
      analogWrite(mtFRp,FRconst+FRvar);
      analogWrite(mtBLp,BLconst+BLvar);
      analogWrite(mtBRp,BRconst-BRvar);
      break;
    case 11:
      analogWrite(mtFLp,FLconst+FLvar);
      analogWrite(mtFRp,FRconst-FRvar);
      analogWrite(mtBLp,BLconst-BLvar);
      analogWrite(mtBRp,BRconst+BRvar);
      break;
    case 12:
      analogWrite(mtFLp,FLconst);
      analogWrite(mtFRp,FRconst);
      analogWrite(mtBLp,BLconst);
      analogWrite(mtBRp,BRconst);
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
  for(int i=0;i<sizeof(OPS)/sizeof(OPS[0]); i++){
    if (req.indexOf(OPS[i]) != -1) {op(i);}
    break;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Comillas importantes.

  client.flush();
  client.stop();
  Serial.println("Client disconnected.");
}
