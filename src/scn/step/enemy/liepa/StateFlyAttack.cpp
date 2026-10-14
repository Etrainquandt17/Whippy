#include "scn/step/enemy/liepa/StateFlyAttack.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/liepa/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

StateFlyAttack::StateFlyAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
}

StateFlyAttack::~StateFlyAttack() {}

void StateFlyAttack::procAnim() {
    const ParamData& param = obj().param().liepa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mShotFrame) {
        custom.reqShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateShootingFly, Enemy*>(objPtr());
    }
}

void StateFlyAttack::procMove() {
    const ParamData& param = obj().param().liepa();
    obj().move().decel(param.mDecel);
}

void StateFlyAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::liepa
