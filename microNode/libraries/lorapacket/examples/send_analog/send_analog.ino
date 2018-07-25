#include <fram.h>
#include <LoRa.h>
#include <packetEncoder.h>


int counter = 0;

uint8_t AppSKey[] = { 0xC3, 0xC2, 0x4B, 0x73, 0x46, 0x53, 0x57, 0x85, 0x5A, 0x0B, 0xC9, 0xAC, 0x55, 0x3A, 0x6B, 0xB7 };
uint8_t NwkSKey[] = { 0xB2, 0xE3, 0x7A, 0x84, 0xC6, 0xF1, 0x79, 0xD3, 0xE2, 0xE6, 0x1B, 0x8F, 0xF9, 0xB7, 0x19, 0x95 };
uint32_t DevAddr = 0x26011C27;

void setup() {

  LoRa.setPins(25, 30, 26);

  if (!LoRa.begin(868500E3)) {
        digitalWrite(12,HIGH);
    while (1);
  }

  pinMode(2,OUTPUT);

  LoRa.setSpreadingFactor(9);
  LoRa.setCodingRate4(5);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSyncWord(0x34);
  LoRa.enableCrc();

  FRAMinit();
}

void loop() {

  uint8_t value = FRAMread(0);
  value++;
  FRAMwrite(0, value);

  uint16_t raw = analogRead(A4);
  uint16_t volt = (2* raw * 3300)/1024;
  
  uint8_t payload[3];
  payload[0] = value;
  payload[1] = uint8_t(volt >> 8);
  payload[2] = uint8_t(volt);
  
  uint8_t payloadLength = 3;
  
  uint8_t buffer1[MAXPAYLOAD];
  uint8_t len = generatePacket(payload, payloadLength, DevAddr, NwkSKey, AppSKey, buffer1);

  // send packet
  LoRa.beginPacket();
  
  for(int i = 0; i < len; i++) {
      LoRa.write(buffer1[i]);
  }

  LoRa.endPacket();

  digitalWrite(2,HIGH);
  delay(10000);
}
