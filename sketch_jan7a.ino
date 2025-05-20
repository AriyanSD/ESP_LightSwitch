#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// Wi-Fi Configuration
const char* ssid = "Wifi SSID ";
const char* password = "Wifi Password";
const int webSocketServerPort = 81;

const int ledPin = D1;
const int togglePin = D2;

WebSocketsServer webSocket = WebSocketsServer(webSocketServerPort);
ESP8266WebServer server(80);

volatile bool toggleRequest = false;
bool ledState = false;

void ICACHE_RAM_ATTR rfToggleISR() {
  toggleRequest = true;
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      Serial.printf("Received text: %s\n", payload);
      if (strcmp((char*)payload, "toggleLED") == 0) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);
        Serial.print("LED toggled via WebSocket: ");
        Serial.println(ledState ? "ON" : "OFF");
      }
      break;
    default:
      break;
  }
}

void handleRoot() {
  server.send(200, "text/html", readFile("/index.html"));
}

String readFile(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return String();
  }
  String content = "";
  while (file.available()) {
    content += (char)file.read();
  }
  file.close();
  return content;
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(togglePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(togglePin), rfToggleISR, CHANGE);

  // Static IP configuration , you can change it according to your router 
  IPAddress local_IP(192, 168, 1, 247);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("Device IP address: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin()) {
    Serial.println("Failed to initialize SPIFFS");
    return;
  }

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
  webSocket.loop();
  server.handleClient();

  if (toggleRequest) {
    toggleRequest = false;
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.print("LED toggled via RF: ");
    Serial.println(ledState ? "ON" : "OFF");
  }
}
