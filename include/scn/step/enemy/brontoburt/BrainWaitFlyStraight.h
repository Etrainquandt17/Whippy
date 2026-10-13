#ifndef SCN_STEP_ENEMY_BRONTOBURT_BRAINWAITFLYSTRAIGHT_H
#define SCN_STEP_ENEMY_BRONTOBURT_BRAINWAITFLYSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

class BrainWaitFlyStraight : public BrainBase {
public:
    BrainWaitFlyStraight(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
