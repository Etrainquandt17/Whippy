#include "scn/step/boss/fattybuffer/StateStampFall.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateStampLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

const StampParam& t_param(Boss& boss) {
    const Param& param = boss.param().fattybuffer();
    return boss.angry().isAngry() ? param.mStampAngry : param.mStamp;
}

}

StateStampFall::StateStampFall(Boss* boss) : StateBase(boss), mCount(0), mStartY(0.0f) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xE);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
    obj().move().resetVelocity();
    mStartY = obj().location().pos().y;
}

StateStampFall::~StateStampFall() {}

void StateStampFall::procAnim() {
    const StampParam& param = t_param(obj());
    if (mCount < param.mFallFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateStampLanding, Boss*>(objPtr());
    }
}

void StateStampFall::procMove() {
    const StampParam& param = t_param(obj());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mFallFrame);
    hel::math::Vector3 pos = obj().location().pos();
    pos.y = hel::math::Math::Interpolate(mStartY + param.mHoldHeight, obj().basePos().y, t);
    obj().location().setPos(pos);
}

void StateStampFall::procFixPos() {}

}
}
}
}
