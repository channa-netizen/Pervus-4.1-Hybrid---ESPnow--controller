#include <cassert>
#include "../usermods/GameControllerUART/PerformancePresetPolicy.h"

int main() {
  assert(transitionForPreset(1) == 700);
  assert(transitionForPreset(6) == 700);
  assert(transitionForPreset(9) == 0);
  assert(transitionForPreset(10) == 0);
  assert(transitionForPreset(11) == 0);
  assert(transitionForPreset(12) == 0);
  assert(transitionForPreset(13) == 700);
  assert(transitionForPreset(250) == 700);
  return 0;
}
