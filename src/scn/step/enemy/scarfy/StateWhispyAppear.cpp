#include "scn/step/enemy/scarfy/StateWhispyAppear.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/scarfy/ParamData.h"
#include "scn/step/enemy/scarfy/StateChase.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateWhispyAppear::StateWhispyAppear(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mPhase(0), mBaseY(obj().location().pos().y), mRot(0.0f) {
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(11);
}

StateWhispyAppear::~StateWhispyAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateWhispyAppear::procAnim() {
    mFrame++;
    const ParamData& param = obj().param().scarfy();
    switch (mPhase) {
    case 0:
        mRot += param.mWhispyAppearRotSpeed;
        if (mRot >= 360.0f) {
            mRot -= 360.0f;
        }
        obj().model().rotCtrl().setRotH(mRot);
        if (mFrame == param.mWhispyAppearFrame1) {
            mPhase++;
            mFrame = 0;
            mBaseY = obj().location().pos().y;
            obj().objColl().bodyColl().setStateNormal();
        }
        break;
    case 1:
        if (mFrame == param.mWhispyAppearFrame2) {
            mPhase++;
            mFrame = 0;
        }
        break;
    default:
        obj().stateChanger().setNextState<StateChase, Enemy*>(objPtr());
        break;
    }
}

void StateWhispyAppear::procMove() {
    const ParamData& param = obj().param().scarfy();
    switch (mPhase) {
    case 0: {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mWhispyAppearFrame1);
        Vector3 pos = obj().location().pos();
        pos.y = mBaseY - param.mWhispyAppearHeight1 * Math::SinDegF(90.0f * rate);
        obj().location().setPos(pos);
        break;
    }
    case 1: {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mWhispyAppearFrame2);
        Vector3 pos = obj().location().pos();
        pos.y = mBaseY + param.mWhispyAppearHeight2 * Math::SinDegF(90.0f * rate);
        obj().location().setPos(pos);
        break;
    }
    }
}

void StateWhispyAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::scarfy
