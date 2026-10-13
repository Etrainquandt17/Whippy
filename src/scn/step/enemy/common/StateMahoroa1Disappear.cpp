#include "scn/step/enemy/common/StateMahoroa1Disappear.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateMahoroa1Disappear::StateMahoroa1Disappear(Enemy* enemy) : StateBase(enemy), mAlgorithm(*enemy) {
    obj().model().reqScript(0);
    obj().model().rotCtrl().initRotV(0.0f);
}

StateMahoroa1Disappear::~StateMahoroa1Disappear() {}

void StateMahoroa1Disappear::procAnim() {
    mAlgorithm.procAnim();
    if (mAlgorithm.isEnd()) {
        obj().dead();
    }
}

void StateMahoroa1Disappear::procMove() {
    mAlgorithm.procMove();
}

void StateMahoroa1Disappear::procFixPos() {}

}}}}  // namespace scn::step::enemy::common
