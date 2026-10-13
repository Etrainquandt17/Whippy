#include "scn/step/enemy/bladeknight/StateAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/bladeknight/Custom.h"
#include "scn/step/enemy/bladeknight/ParamData.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateAttack::procMove() {
    const ParamData& param = obj().param().bladeknight();
    if (mFrame == param.mAttackMoveFrame) {
        f32 speed = param.mAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    if (!hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getWalkFlag() && mFrame == param.mAttackBackFrame) {
        f32 speed = -param.mAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
    if (obj().cliffChecker().isCliff()) {
        obj().move().resetSpeedH();
    }
}

}}}}  // namespace scn::step::enemy::bladeknight
