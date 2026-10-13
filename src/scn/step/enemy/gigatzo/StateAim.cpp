#include "scn/step/enemy/gigatzo/StateAim.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "nw4r/math/math_arithmetic.h"
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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/gigatzo/Custom.h"
#include "scn/step/enemy/gigatzo/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

StateAim::StateAim(Enemy* enemy) : StateBase(enemy), mFrame(0), mFrame2(0), mFrame3(0), mAngle(0.0f) {
    obj().footState().setGround();
    const ParamData& param = obj().param().gigatzo();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 angle = roundAngle(custom.aimAngle());
    mStartAngle = angle;
    mMidAngle = angle;
    mMidAngle += custom.playerAngle() > custom.aimAngle() ? 45.0f : -45.0f;
    angle = roundAngle(mMidAngle);
    mMidAngle = angle;
    mEndAngle = angle;
    mEndAngle += custom.playerAngle() > custom.aimAngle() ? param.mAimSwing : -param.mAimSwing;
    custom.setWaitEffect();
}

StateAim::~StateAim() {
    obj().effect().normal().release();
}

void StateAim::procAnim() {
    const ParamData& param = obj().param().gigatzo();
    u32 end1 = param.mAimFrame1;
    u32 end2 = end1 + param.mAimFrame2;
    u32 end3 = end2 + param.mAimFrame3;
    mFrame++;
    if (mFrame < end1) {
        mAngle = mStartAngle + static_cast<f32>(mFrame) * (mMidAngle - mStartAngle) / static_cast<f32>(param.mAimFrame1);
    } else if (end1 <= mFrame && mFrame < end2) {
        mFrame2++;
        mAngle = mMidAngle + static_cast<f32>(mFrame2) * (mEndAngle - mMidAngle) / static_cast<f32>(param.mAimFrame2);
    } else if (end2 <= mFrame && mFrame < end3) {
        mFrame3++;
        mAngle = mEndAngle + static_cast<f32>(mFrame3) * (mMidAngle - mEndAngle) / static_cast<f32>(param.mAimFrame3);
    } else {
        obj().brainCtrl().toValid();
    }
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAimAngle(mAngle);
}

void StateAim::procMove() {
    if (obj().footState().isAir()) {
        obj().move().airDecelFall(obj().param().common().mDecel, obj().param().common().mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateAim::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().footState().setGround();
    } else {
        obj().footState().setAir();
    }
}

f32 StateAim::roundAngle(f32 angle) {
    return nw4r::math::FFloor((angle + 22.5f) / 45.0f) * 45.0f;
}

}
}
}
}
