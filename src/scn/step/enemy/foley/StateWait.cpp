#include "scn/step/enemy/foley/StateWait.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/foley/ParamData.h"
#include "scn/step/enemy/foley/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mIsReady(false) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    const ParamData& param = obj().param().foley();
    if (2.0f == obj().model().anim().frame()) {
        mIsReady = true;
    }
    if (mIsReady) {
        f32 top = obj().comp().mainCamera().getViewRect()._0;
        bool isInRange = Utility::IsHeroInRange(obj(), 0.0f, -param.mRangeH, -param.mWaitRangeV, param.mWaitRangeV);
        if (top - param.mCameraMargin >= obj().location().pos().y && isInRange) {
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    }
}

void StateWait::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

}}}}  // namespace scn::step::enemy::foley
