#include "scn/step/enemy/bladeknight/StateStepBack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/bladeknight/Custom.h"
#include "scn/step/enemy/bladeknight/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

StateStepBack::StateStepBack(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().bladeknight();
    obj().footState().setGround();
    obj().model().reqScript(9);
    f32 speed = obj().target().isRightDir() ? -param.mStepBackSpeed : param.mStepBackSpeed;
    obj().move().setSpeedH(speed);
}

StateStepBack::~StateStepBack() {}

void StateStepBack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateStepBack::procMove() {
    const ParamData& param = obj().param().bladeknight();
    if (obj().model().anim().frame() >= param.mStepBackDecelFrame) {
        obj().move().groundDecel(param.mStepBackDecel);
    } else {
        obj().move().groundDecel(gobj::MoveParamDecel::Zero());
    }
}

void StateStepBack::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
    if (custom.backStepCliffChk()) {
        obj().move().resetSpeedH();
    }
}

}}}}  // namespace scn::step::enemy::bladeknight
