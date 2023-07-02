// ReadLongpack example

#include <assert.h>
#include <Longpack.h>

#define CAN_PACK_1_SIZE 8
#define CAN_PACK_2_SIZE 1

#define CMD_M_VERSIONS_REQUEST 11

// Data readed from any CAN device:
// Longpack for module: Header
uint8_t canBusData0[CAN_PACK_1_SIZE] = {0xAA, 0x55, 0x00, 0x01, 0x00, 0x01, 0xFF, 0xF4};
// Longpack for module: Data (CMD_M_VERSIONS_REQUEST)
uint8_t canBusData1[CAN_PACK_2_SIZE] = {CMD_M_VERSIONS_REQUEST};

///////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  // Longpack reader
  LongpackReader reader;

  // Read first chunk
  ERR_E doing = reader.read(canBusData0, CAN_PACK_1_SIZE);
  assert(doing == E_DOING);
  Serial.println("First assert passed, cmd is incomplete");

  // Read second chunk
  ERR_E completed = reader.read(canBusData1, CAN_PACK_2_SIZE);
  assert(completed == E_TRUE);
  Serial.println("Second assert passed, cmd is complete");

  // Read command
  uint8_t command = reader.cmd[0];
  assert(command == CMD_M_VERSIONS_REQUEST);
  Serial.println("Third assert passed, cmd is CMD_M_VERSIONS_REQUEST");
}

///////////////////////////////////////////////////////////////////////////////

void loop() {
  // Nothing to do
}
