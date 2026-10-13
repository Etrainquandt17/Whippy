#ifndef SCN_STEP_ENEMY_COMMON_STATEMAHOROA1APPEAR_H
#define SCN_STEP_ENEMY_COMMON_STATEMAHOROA1APPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"
#include "scn/step/enemy/algorithm/AlgorithmMahoroa1Appear.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateMahoroa1Appear : public StateBase {
public:
    StateMahoroa1Appear(Enemy* enemy, bool _8);
    virtual ~StateMahoroa1Appear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    algorithm::AlgorithmMahoroa1Appear mAlgorithm;
    bool _10;
};

}
}
}
}

#endif
