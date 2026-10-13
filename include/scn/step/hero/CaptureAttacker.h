#ifndef SCN_STEP_HERO_CAPTUREATTACKER_H
#define SCN_STEP_HERO_CAPTUREATTACKER_H

#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace enemy {
class Enemy;
}

namespace hero {

// TODO: members and the other functions.
class CaptureAttacker {
public:
    util::ObjRefHandle<enemy::Enemy> chkCaptureEnemy();
};

}
}
}

#endif
