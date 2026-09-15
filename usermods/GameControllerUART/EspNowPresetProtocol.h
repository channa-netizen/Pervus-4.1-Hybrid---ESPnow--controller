#pragma once
#include <stddef.h>
#include <stdint.h>

static constexpr uint8_t ESPNOW_PRESET_PROTOCOL_VERSION = 1;
static constexpr uint8_t ESPNOW_CMD_PRESET = 1;

struct __attribute__((packed)) EspNowPresetPacket {
  uint8_t magic0;
  uint8_t magic1;
  uint8_t version;
  uint8_t command;
  uint8_t preset;
  uint8_t reserved;
  uint16_t sequence;
};

static_assert(sizeof(EspNowPresetPacket) == 8, "ESP-NOW preset packet must be 8 bytes");

constexpr EspNowPresetPacket makeEspNowPresetPacket(uint8_t preset, uint16_t sequence) {
  return {'P', 'V', ESPNOW_PRESET_PROTOCOL_VERSION, ESPNOW_CMD_PRESET, preset, 0, sequence};
}

inline bool decodeEspNowPresetPacket(const uint8_t* data, size_t len, uint8_t& presetOut) {
  if (data == nullptr || len != sizeof(EspNowPresetPacket)) return false;

  const auto* packet = reinterpret_cast<const EspNowPresetPacket*>(data);
  if (packet->magic0 != 'P' || packet->magic1 != 'V') return false;
  if (packet->version != ESPNOW_PRESET_PROTOCOL_VERSION) return false;
  if (packet->command != ESPNOW_CMD_PRESET) return false;
  if (packet->preset < 1 || packet->preset > 250) return false;

  presetOut = packet->preset;
  return true;
}
