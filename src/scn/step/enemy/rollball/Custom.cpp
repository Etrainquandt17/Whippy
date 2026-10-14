#include "scn/step/enemy/rollball/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/rollball/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsBallIron(false), mSize(0), mIsPlayingSound(false) {
    obj().cliffChecker().setValid(false);
}

bool Custom::onInit() {
    switch (obj().variation()) {
    default:
        mSize = 0;
        break;
    case 0xbc:
    case 0xbe:
    case 0x108:
    case 0x14b:
        mSize = 1;
        break;
    case 0xbd:
    case 0xbf:
    case 0x109:
    case 0x14c:
        mSize = 2;
        break;
    }
    if (obj().kind() == 0x38) {
        mIsBallIron = true;
    }
    obj().culling().setValid(false);
    obj().model().rotCtrl().setValid(false);
    obj().cliffChecker().setValid(false);
    obj().captureReceiver().setCanCapture(false);
    obj().objColl().clearBodyColl();
    obj().objColl().clearAttack();
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

f32 Custom::getRadius() {
    const ParamData& param = obj().param().rollball();
    f32 radius;
    switch (mSize) {
    default:
        radius = param.mRadius[0];
        break;
    case 1:
        radius = param.mRadius[1];
        break;
    case 2:
        radius = param.mRadius[2];
        break;
    }
    return radius;
}

void Custom::addAttack() {
    obj().objColl().clearBodyColl();
    obj().objColl().bodyColl().setStateHitOnly();
    obj().objColl().clearAttack();
    obj().objColl().addBodyColl(1, getRadius() - 0.3f);
    obj().objColl().addAttack(0, 1, getRadius() - 0.3f);
    obj().objColl().addAttack(1, 1, getRadius());
    if (obj().kind() == 0x5b) {
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x23b));
        obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x234));
    } else if (obj().kind() == 0x63) {
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x23c));
        obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x235));
    } else {
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x23a));
        obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x233));
    }
}

int Custom::getSize() {
    return mSize;
}

bool Custom::isBallIron() {
    return mIsBallIron;
}

bool Custom::isPlayingSound() {
    return mIsPlayingSound;
}

void Custom::setPlayingSound(bool isPlayingSound) {
    mIsPlayingSound = isPlayingSound;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::rollball
