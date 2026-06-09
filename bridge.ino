#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer server(80);

void handlePost() {
    if (server.method() == HTTP_POST) {
        StaticJsonDocument<200> doc;
        deserializeJson(doc, server.arg("plain"));
        
        int threshold = doc["params"]["limit"];
        
        // Forward to Zybo via UART (Pmod pins)
        Serial1.write(threshold); 
        
        server.send(200, "application/json", "{\"status\":\"updated\"}");
    }
}

void setup() {
    Serial1.begin(9600, SERIAL_8N1, 16, 17); // Pmod TX/RX
    server.on("/api/config", handlePost);
    server.begin();
}

void loop() { server.handleClient(); }