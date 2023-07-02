// WriteLongpack example

#include <assert.h>
#include <Longpack.h>

#define CMD_PACK_SIZE 8

#define CMD_S_VERSIONS_REACK 12
#define VERSION "v1.9.2"

// Data sending from SM2 module:
// Cmd for controller: CMD_S_VERSIONS_REACK, Hex: ..v.1.9.2

uint8_t cmdData1[32];
uint8_t index = 0;

///////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  // Prepare data
  cmdData1[index++] = CMD_S_VERSIONS_REACK;
  cmdData1[index++] = 0;

  size_t length = strlen(VERSION);
  memcpy(cmdData1 + index, VERSION, length);
  index += length;

  // Longpack packer
  LongpackPacker packer;

  // Pack longpack
  packer.pack(cmdData1, index);

  // Assert longpack
  uint8_t assertion[16] = {0xAA, 0x55, 0x00, 0x08, 0x00, 0x08, 0x21, 0x63, 0x0C, 0x00, 0x76, 0x31, 0x2E, 0x39, 0x2E, 0x32};
  for (uint8_t i = 0; i < 16; i++) {
    assert(packer.read() == assertion[i]);
    Serial.print("Assert ");
    Serial.print(i);
    Serial.println(" is checked.");
  }
}

///////////////////////////////////////////////////////////////////////////////

void loop() {
  // Nothing to do
}
