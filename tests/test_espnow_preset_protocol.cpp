#include <cassert>
#include <cstdint>
#include "../usermods/GameControllerUART/EspNowPresetProtocol.h"

int main() {
  EspNowPresetPacket packet = makeEspNowPresetPacket(7, 42);
  assert(sizeof(packet) == 8);
  assert(packet.magic0 == 'P');
  assert(packet.magic1 == 'V');
  assert(packet.version == 1);
  assert(packet.command == ESPNOW_CMD_PRESET);
  assert(packet.preset == 7);
  assert(packet.sequence == 42);

  uint8_t preset = 0;
  assert(decodeEspNowPresetPacket(reinterpret_cast<const uint8_t*>(&packet), sizeof(packet), preset));
  assert(preset == 7);

  EspNowPresetPacket badMagic = packet;
  badMagic.magic0 = 'X';
  assert(!decodeEspNowPresetPacket(reinterpret_cast<const uint8_t*>(&badMagic), sizeof(badMagic), preset));

  EspNowPresetPacket badVersion = packet;
  badVersion.version = 2;
  assert(!decodeEspNowPresetPacket(reinterpret_cast<const uint8_t*>(&badVersion), sizeof(badVersion), preset));

  EspNowPresetPacket badPreset = packet;
  badPreset.preset = 0;
  assert(!decodeEspNowPresetPacket(reinterpret_cast<const uint8_t*>(&badPreset), sizeof(badPreset), preset));

  assert(!decodeEspNowPresetPacket(reinterpret_cast<const uint8_t*>(&packet), sizeof(packet) - 1, preset));
  return 0;
}
