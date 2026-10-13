#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"

#include "scn/step/enemy/Enemy.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

void WhispyAppleUtility::ReqFallSE(Enemy& enemy) {
    u32 se = 0x316;
    if (enemy.kind() == 0xa) {
        se = 0x31b;
    }
    enemy.soundSE().start(se);
}

void WhispyAppleUtility::ReqBoundSE(Enemy& enemy) {
    u32 se = 0x317;
    switch (enemy.kind()) {
    case 0xa:
        se = 0x31f;
        break;
    case 1:
    case 2:
        se = 0x31e;
        break;
    }
    enemy.soundSE().start(se);
}

void WhispyAppleUtility::ReqBoundSEIfGordo(Enemy& enemy) {
    if (enemy.kind() == 0xa) {
        enemy.soundSE().start(0x31f);
    }
}

}
}
}
}
