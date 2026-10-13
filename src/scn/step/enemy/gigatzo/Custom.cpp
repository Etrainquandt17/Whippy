#include "scn/step/enemy/gigatzo/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/gigatzo/ParamData.h"
#include "scn/step/map/LandManager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mAimAngle(0.0f), mIsBackAttack(false), mIsAir(false) {
    switch (obj().variation()) {
    case 0:
    case 0x3c:
    case 0x4e:
    case 0x52:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0xc6:
    case 0xc7:
    case 0xc8:
        mIsBackAttack = false;
        mIsAir = false;
        break;
    case 0x14d:
    case 0x14e:
    case 0x14f:
    case 0x150:
        mIsBackAttack = false;
        mIsAir = true;
        break;
    default:
        mIsBackAttack = true;
        mIsAir = false;
        break;
    }
}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().culling().setValid(false);
    f32 diameter = obj().param().gigatzo().mShadowDiameter;
    obj().shadow().changeDiameter(diameter);
    obj().cliffChecker().setValid(false);
    obj().objColl().clearBodyColl();
    if (!mIsBackAttack) {
        obj().objColl().addBodyColl(0, 0.9f, hel::math::Vector2(0.0f, 1.6f), hel::math::Vector2(0.0f, 0.7f));
        obj().model().model().nodes().at(7).setVisibility(false);
        obj().model().model().nodes().at(8).setVisibility(false);
        if (obj().variation() != 0x4e && obj().variation() != 0x93 && obj().variation() != 0xc8) {
            setAimAngle(Utility::GetRotByDirType(obj()));
        }
        if (mIsAir) {
            obj().mapColl().setValid(false);
        }
    } else {
        obj().mapColl().setValid(false);
        obj().nururi().setValid(false);
        obj().vacuumReceiver().setIsValid(false);
        setAimAngle(0.0f);
        hel::math::Vector3 pos = obj().location().pos();
        pos.z -= obj().param().gigatzo().mBackZ;
        obj().location().setPos(pos);
    }
    setModelColor();
    return false;
}

void Custom::onProcFixPos() {
    setModelColor();
    const ParamData& param = obj().param().gigatzo();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    if (pos.x < 0.0f || static_cast<f32>(obj().comp().mapLandManager().native().gridWidth()) < pos.x) {
        obj().dead();
        return;
    }
    hel::geo::Rect rect = obj().culling().calcCullingRect();
    rect._0 += mIsBackAttack ? param.mCullingMarginBack : param.mCullingMargin;
    rect._4 -= 6.0f;
    rect._8 -= mIsBackAttack ? param.mCullingMarginBack : param.mCullingMargin;
    rect._C += mIsBackAttack ? param.mCullingMarginBack : param.mCullingMargin;
    if (!rect.isInclude(pos.x, pos.y)) {
        obj().dead();
        return;
    }
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

bool Custom::onOutWater() {
    return onInWater();
}

f32 Custom::aimAngle() const {
    return mAimAngle;
}

bool Custom::isBackAttack() {
    return mIsBackAttack;
}

bool Custom::isAir() {
    return mIsAir;
}

void Custom::setAimAngle(f32 angle) {
    mAimAngle = angle;
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, 0.0f, -1.0f * angle));
    node.localMtx().setRTMtx(mtx);
}

f32 Custom::playerAngle() {
    hel::math::Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    g3d::NodeAccessor node = obj().model().model().nodes().at(2);
    hel::math::Vector2 nodePos = node.worldMtx().getT().getXY();
    playerPos -= nodePos;
    f32 angle = hel::math::Math::Atan2DegF(playerPos.x, playerPos.y);
    if (angle > 90.0f) {
        angle = 90.0f;
    }
    if (angle < -90.0f) {
        angle = -90.0f;
    }
    return angle;
}

bool Custom::isPlayerInAimArea() {
    f32 aimAngle = mAimAngle;
    f32 diff = hel::math::Math::AbsF32(playerAngle() - aimAngle);
    return diff <= obj().param().gigatzo().mAimArea;
}

void Custom::setWaitEffect() {
    switch (obj().kind()) {
    case 0x39:
        if (mIsBackAttack) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x550), 5);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x550), 6);
        } else {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54f), 5);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54f), 6);
        }
        break;
    case 0x49:
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x58), 1);
        break;
    }
}

int Custom::setWaitAttackTime() {
    const ParamData& param = obj().param().gigatzo();
    switch (obj().level()) {
    case 0:
        return param.mWaitAttackTime[0];
    case 1:
        return param.mWaitAttackTime[1];
    case 2:
        return param.mWaitAttackTime[2];
    case 3:
        return param.mWaitAttackTime[3];
    case 4:
        return param.mWaitAttackTime[4];
    default:
        return param.mWaitAttackTime[5];
    }
}

int Custom::setWaitBackAttackTime() {
    const ParamData& param = obj().param().gigatzo();
    switch (obj().level()) {
    case 0:
        return param.mWaitBackAttackTime[0];
    case 1:
        return param.mWaitBackAttackTime[1];
    case 2:
        return param.mWaitBackAttackTime[2];
    default:
        return param.mWaitBackAttackTime[3];
    }
}

int Custom::setWaitBackAttackMoreTime() {
    const ParamData& param = obj().param().gigatzo();
    switch (obj().level()) {
    case 0:
        return param.mWaitBackAttackMoreTime[0];
    case 1:
        return param.mWaitBackAttackMoreTime[0];
    case 2:
        return param.mWaitBackAttackMoreTime[1];
    default:
        return param.mWaitBackAttackMoreTime[2];
    }
}

void Custom::setModelColor() {
    const ParamData& param = obj().param().gigatzo();
    GXColor color = {0xff, 0xff, 0xff, 0};
    switch (obj().variation()) {
    case 0x4f:
    case 0x53:
        color = param.mColor[0];
        break;
    case 0xfb:
    case 0xfc:
        color = param.mColor[1];
        break;
    case 0x94:
    case 0x95:
        color = param.mColor[2];
        break;
    case 0xfd:
    case 0xfe:
        color = param.mColor[3];
        break;
    case 0xc9:
    case 0xca:
        color = param.mColor[4];
        break;
    case 0xff:
    case 0x100:
        color = param.mColor[5];
        break;
    case 0x10e:
    case 0x10f:
        color = param.mColor[6];
        break;
    }
    obj().flash().setEnfAlways(color);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
