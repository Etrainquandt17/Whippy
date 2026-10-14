#include "scn/step/enemy/pierce/StateFlySinCurve.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/pierce/Custom.h"
#include "scn/step/enemy/pierce/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

StateFlySinCurve::StateFlySinCurve(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mAngle(0.0f), mIsAttack(false), mIsAttackEnd(false) {
    const ParamData& param = obj().param().pierce();
    obj().footState().setAir();
    obj().model().reqScript(7);
    mSpeedH = param.mSinSpeedH * (obj().target().isRightDir() ? 1.0f : -1.0f);
}

StateFlySinCurve::~StateFlySinCurve() {}

void StateFlySinCurve::procAnim() {
    const ParamData& param = obj().param().pierce();
    bool isInArea = DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInAimArea();
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (isInArea && !mIsAttack) {
        obj().model().reqScript(9);
        mIsAttack = true;
    }
    if (obj().model().isAllEnd()) {
        if (index == 5) {
            if (obj().target().isRightDir()) {
                obj().model().reqScript(11);
            } else {
                obj().model().reqScript(10);
            }
        } else if (index == 6 || index == 7) {
            obj().model().reqScript(7);
            mIsAttackEnd = true;
        }
    }
    if (mIsAttack) {
        mFrame++;
        if (mFrame == param.mAttackFrame) {
            mIsAttack = false;
            mIsAttackEnd = false;
            mFrame = 0;
        }
    } else {
        mFrame = 0;
    }
}

void StateFlySinCurve::procMove() {
    const ParamData& param = obj().param().pierce();
    if (!mIsAttack || mIsAttackEnd) {
        mAngle += param.mSinAngleSpeed;
        if (mAngle >= 360.0f) {
            mAngle -= 360.0f;
        }
        f32 speedV = param.mSinSpeedV * Math::CosDegF(mAngle);
        obj().move().setSpeedV(speedV);
        obj().move().setSpeedH(mSpeedH);
    } else {
        obj().move().resetVelocity();
    }
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

void StateFlySinCurve::procFixPos() {
    const ParamData& param = obj().param().pierce();
    if (obj().mapColl().result().isHitWallFront() || Utility::ChkNururiByDir(obj(), 0.0f)) {
        mSpeedH = -mSpeedH;
        obj().target().setIsRightDir(mSpeedH >= 0.0f);
    }
    if (obj().mapColl().result().mIsHitRoof) {
        mAngle = 90.0f;
    } else if (obj().mapColl().result().mIsHitFloor) {
        mAngle = 270.0f;
    }
}

}}}}  // namespace scn::step::enemy::pierce
