#ifndef SCN_STEP_ENEMY_BABUT_BRAINDOUBTER_H
#define SCN_STEP_ENEMY_BABUT_BRAINDOUBTER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

class BrainDoubter : public BrainBase {
public:
    BrainDoubter(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
