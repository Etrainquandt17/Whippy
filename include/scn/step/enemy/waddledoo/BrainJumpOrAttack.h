#ifndef SCN_STEP_ENEMY_WADDLEDOO_BRAINJUMPORATTACK_H
#define SCN_STEP_ENEMY_WADDLEDOO_BRAINJUMPORATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class BrainJumpOrAttack : public BrainBase {
public:
    BrainJumpOrAttack(Enemy& enemy);
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
