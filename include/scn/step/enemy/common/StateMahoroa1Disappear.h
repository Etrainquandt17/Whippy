#ifndef SCN_STEP_ENEMY_COMMON_STATEMAHOROA1DISAPPEAR_H
#define SCN_STEP_ENEMY_COMMON_STATEMAHOROA1DISAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"
#include "scn/step/enemy/algorithm/AlgorithmMahoroa1Disappear.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateMahoroa1Disappear : public StateBase {
public:
    StateMahoroa1Disappear(Enemy* enemy);
    virtual ~StateMahoroa1Disappear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    algorithm::AlgorithmMahoroa1Disappear mAlgorithm;
};

}
}
}
}

#endif
