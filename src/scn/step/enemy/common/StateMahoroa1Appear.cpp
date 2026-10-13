#include "scn/step/enemy/common/StateMahoroa1Appear.h"

#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateMahoroa1Appear::StateMahoroa1Appear(Enemy* enemy, bool _10) : StateBase(enemy), mAlgorithm(*enemy), _10(_10) {
    obj().model().reqScript(6);
}

StateMahoroa1Appear::~StateMahoroa1Appear() {}

void StateMahoroa1Appear::procAnim() {
    mAlgorithm.procAnim();
    if (mAlgorithm.isEnd()) {
        if (_10) {
            obj().stateChanger().setNextState<StateFly, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
        }
    }
}

void StateMahoroa1Appear::procMove() {
    mAlgorithm.procMove();
}

void StateMahoroa1Appear::procFixPos() {}

}
}
}
}
