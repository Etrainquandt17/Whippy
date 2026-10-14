#include "scn/step/enemy/waddledee/StateWhispyFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/waddledee/ParamData.h"
#include "scn/step/enemy/waddledee/StateWhispyLanding.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateWhispyFall::StateWhispyFall(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    obj().footState().setAir();
    obj().model().reqScript(15);
}

StateWhispyFall::~StateWhispyFall() {
    obj().model().unsetCustomMtx();
}

void StateWhispyFall::procAnim() {
    const ParamData& param = obj().param().waddledee();
    mRot += param.mWhispyFallRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    Vector3 rot(mRot, 0.0f, 0.0f);
    Utility::SetCustomMtxRotate(obj(), rot);
}

void StateWhispyFall::procMove() {
    const ParamData& param = obj().param().waddledee();
    obj().move().airDecelFall(obj().param().common().mDecel, param.mWhispyFallFall);
}

void StateWhispyFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateWhispyLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::waddledee
