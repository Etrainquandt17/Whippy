#include "scn/step/enemy/kabu/StateTeleport.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/kabu/Custom.h"
#include "scn/step/enemy/kabu/ParamData.h"
#include "scn/step/enemy/kabu/StateFall.h"

using app::Random;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateTeleport::StateTeleport(Enemy* enemy)
    : StateBase(enemy), mStep(0), mSpeedH(0.0f), mSpeedV(0.0f), mAngle(0.0f), mFrame(0), mMoveFrame(0), mIsHit(false) {
    const ParamData& param = obj().param().kabu();
    int rand = Random::Rand(0, 4);
    mWaitFrame = param.mTeleportWaitFrame + rand * param.mTeleportWaitFrameStep;
    obj().footState().setAir();
    obj().model().reqScript(1);
    f32 x = Random::RandF(param.mTeleportDistXMin, param.mTeleportDistXMax);
    f32 y = Random::RandF(param.mTeleportDistYMin, param.mTeleportDistYMax);
    if (Random::Rand(0, 2) == 0) {
        x *= -1.0f;
    }
    mSpeedH = x / param.mTeleportMoveFrame;
    mSpeedV = y / param.mTeleportMoveFrame;
}

StateTeleport::~StateTeleport() {}

void StateTeleport::procAnim() {
    const ParamData& param = obj().param().kabu();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    u32 index = obj().model().anim().currentG3DAnimIndex();
    mFrame++;
    switch (mStep) {
    case 0:
        if (mFrame == mWaitFrame) {
            obj().model().reqScript(10);
            obj().nururi().setValid(false);
            obj().objColl().clearBodyColl();
            obj().vacuumReceiver().setIsValid(false);
            obj().water().setForbidEffect(true);
            custom.setIsInvisible(true);
            mStep = 1;
            mFrame = 0;
        }
        break;
    case 1:
        if (mFrame < param.mTeleportBlinkFrame) {
            blinkModel();
        }
        if (obj().model().isAllEnd()) {
            obj().model().setVisibility(false);
            obj().shadow().setVisibility(false);
            obj().mapColl().setValid(false);
            mStep = 2;
        }
        break;
    case 3:
        if (index == 9) {
            obj().model().reqScript(11);
            obj().model().setVisibility(true);
            obj().shadow().setVisibility(true);
            mFrame = 0;
        } else if (index == 10) {
            if (mFrame < param.mTeleportBlinkFrame) {
                blinkModel();
            }
            if (obj().model().isAllEnd()) {
                obj().model().setVisibility(true);
                obj().shadow().setVisibility(true);
                obj().nururi().setValid(true);
                obj().objColl().addBodyColl(1, param.mBodyCollRadius);
                obj().vacuumReceiver().setIsValid(true);
                obj().water().setForbidEffect(false);
                custom.setIsInvisible(false);
                if (obj().water().isInWater()) {
                    obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(objPtr());
                } else {
                    obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
                }
            }
        }
        break;
    }
}

void StateTeleport::procMove() {
    const ParamData& param = obj().param().kabu();
    if (mStep != 2) {
        mAngle += param.mTeleportFloatAngleSpeed;
        if (mAngle >= 360.0f) {
            mAngle -= 360.0f;
        }
        f32 speed = param.mTeleportFloatSpeed * Math::CosDegF(mAngle);
        obj().move().setSpeedV(speed);
    } else {
        if (mMoveFrame == 0) {
            Vector3 pos = Utility::GetNearestPlayerPos(obj()).toVector3();
            obj().location().setPos(pos);
        } else if (mMoveFrame == 1) {
            obj().mapColl().setValid(true);
        }
        mMoveFrame++;
        if (mIsHit || mMoveFrame == 0) {
            obj().move().resetVelocity();
        } else {
            obj().move().setSpeedH(mSpeedH);
            obj().move().setSpeedV(mSpeedV);
        }
        if (mMoveFrame == param.mTeleportMoveFrame) {
            obj().move().resetVelocity();
            mStep = 3;
        }
    }
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateTeleport::procFixPos() {
    mIsHit = obj().mapColl().result().isHit();
}

void StateTeleport::blinkModel() {
    if (static_cast<f32>(mFrame % 4) <= 1.0f) {
        obj().model().setVisibility(false);
        obj().shadow().setVisibility(false);
    } else {
        obj().model().setVisibility(true);
        obj().shadow().setVisibility(true);
    }
}

}}}}  // namespace scn::step::enemy::kabu
