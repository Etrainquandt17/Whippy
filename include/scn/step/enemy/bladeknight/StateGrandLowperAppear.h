#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATEGRANDLOWPERAPPEAR_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATEGRANDLOWPERAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "scn/step/enemy/algorithm/AlgorithmGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

class StateGrandLowperAppear : public StateBase {
public:
    StateGrandLowperAppear(Enemy* enemy);
    virtual ~StateGrandLowperAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    algorithm::AlgorithmGrandLowperAppear mAlgorithm;
};

}
}
}
}

#endif
