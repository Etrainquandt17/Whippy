#include "scn/step/enemy/sheld/StateDash.h"

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
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/ParamData.h"
#include "scn/step/enemy/sheld/StateFall.h"
#include "scn/step/enemy/sheld/StateJumpStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateDash::StateDash(Enemy* enemy) : StateBase(enemy), mAccel(0.0f) {
    const ParamData& param = obj().param().sheld();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        mAccel = param.mDashAccel[0];
        break;
    case 1:
        mAccel = param.mDashAccel[1];
        break;
    default:
        mAccel = param.mDashAccel[2];
        break;
    }
    obj().footState().setGround();
    obj().model().reqScript(9);
    obj().model().anim().setFrameRate(param.mDashFrameRate * mAccel);
    obj().move().setSpeedH(0.5f * (mAccel * obj().target().getSign()));
    obj().brainCtrl().toValid();
}

StateDash::~StateDash() {}

void StateDash::procAnim() {}

void StateDash::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(mAccel, 0.001f, 0.001f));
}

void StateDash::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ChkNururiTurn(obj());
    if (obj().mapColl().result()._2) {
        if (custom.isSetPos()) {
            custom.resetPos();
            obj().move().resetSpeedH();
            Utility::Turn(obj());
        } else {
            obj().stateChanger().setNextState<StateJumpStart, Enemy*>(objPtr());
            return;
        }
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sheld
