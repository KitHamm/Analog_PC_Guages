#include <Adafruit_MCP4728.h>
#include <Arduino.h>
#include <Wire.h>
#include "DHTStable.h"
DHTStable DHT;
#define DHT22_PIN 16

Adafruit_MCP4728 mcp;

String t;

void setup() {
  Serial.setTimeout(500);
  Serial.begin(115200);
  if (!mcp.begin()) {
    while (1) {
      delay(10);
    }
  }
  for (int i = 0; i < 340; i++) {
    mcp.setChannelValue(MCP4728_CHANNEL_A, i);
    mcp.setChannelValue(MCP4728_CHANNEL_B, i);
    mcp.setChannelValue(MCP4728_CHANNEL_C, i);
    mcp.setChannelValue(MCP4728_CHANNEL_D, i);
    delay(1);
  }
  for (int i = 340; i > 0; i--) {
    mcp.setChannelValue(MCP4728_CHANNEL_A, i);
    mcp.setChannelValue(MCP4728_CHANNEL_B, i);
    mcp.setChannelValue(MCP4728_CHANNEL_C, i);
    mcp.setChannelValue(MCP4728_CHANNEL_D, i);
    delay(1);
  }
}
void loop() {
  if (Serial.available()) {
    DHT.read22(DHT22_PIN);
    //Serial Read
    String rawCPU = Serial.readStringUntil('\n');
    String rawGPU = Serial.readStringUntil('\n');
    String rawRAM = Serial.readStringUntil('\n');
    // MCP4728
    int rawGaugeTemp;
    if (DHT.getTemperature() < 0) {
      rawGaugeTemp = 0;
    }
    else {
      rawGaugeTemp = map(DHT.getTemperature(), 20.0, 35.0, 0, 340);
    }
    mcp.setChannelValue(MCP4728_CHANNEL_A, map(rawCPU.toInt(), 0, 100, 0, 340));
    mcp.setChannelValue(MCP4728_CHANNEL_B, map(rawGPU.toInt(), 0, 100, 0, 340));
    mcp.setChannelValue(MCP4728_CHANNEL_C, map(rawRAM.toInt(), 0, 100, 0, 340));
    mcp.setChannelValue(MCP4728_CHANNEL_D, rawGaugeTemp);
  }
}
