#include "scn/step/enemy/juckle/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/DamageInfo.h"
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
#include "scn/step/enemy/juckle/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), _8(0), mFollowFlag(false), mAnger(0.0f), mViewVectorRot(0.0f), mDir(false) {
    switch (enemy.dirType()) {
    case 3:
    case 7:
    case 9:
    case 1:
        mDir = true;
        obj().model().rotCtrl().initRotH(-90.0f);
        break;
    default:
        obj().model().rotCtrl().initRotH(90.0f);
        break;
    }
    f32 rot = VectorRot(enemy.dirType());
    obj().model().rotCtrl().initRotV(rot);
    mViewVectorRot = 360.0f - obj().model().rotCtrl().getRotV();
    obj().model().rotCtrl().setValid(false);
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().attackType() == 0x12) {
        return false;
    }
    if (obj().damageInfo().element() == 3) {
        obj().model().rotCtrl().setValid(true);
        obj().model().rotCtrl().resetRot();
        obj().model().unsetCustomMtx();
    }
    return false;
}

void Custom::onCaptured() {
    obj().model().rotCtrl().setValid(true);
    obj().model().rotCtrl().resetRot();
    obj().model().unsetCustomMtx();
}

f32 Custom::VectorRot(map::BinEnemyDirType dirType) {
    const ParamData& param = obj().param().juckle();
    f32 rot = 0.0f;
    switch (dirType) {
    case 4:
        rot = param.mRot[0];
        mAnger = param.mAnger[0];
        break;
    case 7:
        rot = param.mRot[1];
        mAnger = param.mAnger[1];
        break;
    case 3:
        rot = param.mRot[2];
        mAnger = param.mAnger[2];
        break;
    case 9:
        rot = param.mRot[3];
        mAnger = param.mAnger[3];
        break;
    case 5:
        rot = param.mRot[4];
        mAnger = param.mAnger[4];
        break;
    case 8:
        rot = param.mRot[5];
        mAnger = param.mAnger[5];
        break;
    case 2:
        rot = param.mRot[6];
        mAnger = param.mAnger[6];
        break;
    case 6:
        rot = param.mRot[7];
        mAnger = param.mAnger[7];
        break;
    case 0:
        rot = param.mRot[6];
        mAnger = param.mAnger[6];
        break;
    case 1:
        rot = param.mRot[2];
        mAnger = param.mAnger[2];
        break;
    }
    return rot;
}

bool Custom::getFollowFlag() {
    return mFollowFlag;
}

void Custom::onFollowFlag() {
    mFollowFlag = true;
}

bool Custom::myDir() const {
    return mDir;
}

f32 Custom::myAnger() const {
    return mAnger;
}

void Custom::setAnger(f32 anger) {
    mAnger = anger;
}

f32 Custom::getViewVectorRot() {
    return mViewVectorRot;
}

f32 Custom::playerAnger() {
    hel::math::Vector2 pos = Utility::GetNearestPlayerPos(obj());
    pos -= obj().location().pos().getXY();
    return hel::math::Math::Atan2DegF(pos.x, pos.y);
}

bool Custom::isPlayerInArea() {
    const ParamData& param = obj().param().juckle();
    bool result = true;
    f32 anger = mAnger;
    if (!(hel::math::Math::Abs(playerAnger() - anger) <= param.mNearAngle)) {
        f32 anger2 = mAnger;
        bool isFar = hel::math::Math::Abs(playerAnger() - anger2) >= param.mFarAngle;
        if (!isFar) {
            result = false;
        }
    }
    return result;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::juckle
