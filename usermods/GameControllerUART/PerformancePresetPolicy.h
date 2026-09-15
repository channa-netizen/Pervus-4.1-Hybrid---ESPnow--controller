#pragma once
#include <stdint.h>

static constexpr uint16_t NORMAL_PRESET_TRANSITION_MS = 700;
static constexpr uint16_t BANGER_PRESET_TRANSITION_MS = 0;

constexpr uint16_t transitionForPreset(int preset) {
  return (preset >= 9 && preset <= 12)
    ? BANGER_PRESET_TRANSITION_MS
    : NORMAL_PRESET_TRANSITION_MS;
}
