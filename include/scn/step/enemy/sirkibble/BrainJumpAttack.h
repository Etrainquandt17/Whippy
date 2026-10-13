#ifndef SCN_STEP_ENEMY_SIRKIBBLE_BRAINJUMPATTACK_H
#define SCN_STEP_ENEMY_SIRKIBBLE_BRAINJUMPATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

class BrainJumpAttack : public BrainBase {
public:
    BrainJumpAttack(Enemy& enemy);
    virtual bool onLanding();
};

}
}
}
}

#endif
