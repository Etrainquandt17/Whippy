#include "scn/step/enemy/brontoburt/StateWhispyAppear.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/ParamData.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "snd/SERequestor.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

StateWhispyAppear::StateWhispyAppear(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mStep(0), mBaseY(obj().location().pos().y), mRotH(0.0f) {
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(7);
}

StateWhispyAppear::~StateWhispyAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateWhispyAppear::procAnim() {
    mFrame++;
    const ParamData& param = obj().param().brontoburt();
    switch (mStep) {
    case 0:
        mRotH += param.mWhispyRotSpeed;
        if (mRotH >= 360.0f) {
            mRotH -= 360.0f;
        }
        obj().model().rotCtrl().setRotH(mRotH);
        if (mFrame == param.mWhispyAppearFrame) {
            mStep++;
            mFrame = 0;
            mBaseY = obj().location().pos().y;
            obj().objColl().bodyColl().setStateNormal();
        }
        break;
    case 1:
        if (mFrame == param.mWhispyWaitFrame) {
            mStep++;
            mFrame = 0;
        }
        break;
    }
}

void StateWhispyAppear::procMove() {
    const ParamData& param = obj().param().brontoburt();
    switch (mStep) {
    case 0: {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mWhispyAppearFrame);
        Vector3 pos = obj().location().pos();
        pos.y = mBaseY - param.mWhispyDownHeight * Math::SinDegF(90.0f * rate);
        obj().location().setPos(pos);
        break;
    }
    case 1: {
        f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mWhispyWaitFrame);
        Vector3 pos = obj().location().pos();
        pos.y = mBaseY + param.mWhispyUpHeight * Math::SinDegF(90.0f * rate);
        obj().location().setPos(pos);
        break;
    }
    default:
        obj().move().airDecelFall(param.mWhispyDecel, param.mWhispyFall);
        break;
    }
}

void StateWhispyAppear::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().soundSE().start(0x31e);
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::brontoburt
