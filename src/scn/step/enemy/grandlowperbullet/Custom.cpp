#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/enemy/grandlowperbullet/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/hero/Hero.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mTargetPos(enemy.location().pos()), mTargetHero() {}

bool Custom::onInit() {
    reqImageEffect();
    if (obj().size() == 1) {
        obj().captureReceiver().setCanCapture(true);
    }
    return false;
}

bool Custom::onDamaged() {
    return true;
}

bool Custom::onHitPointIsZero() {
    if (obj().variation() == 0x163 && obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        obj().model().unsetCustomMtx();
        return false;
    }
    return false;
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permSoundSE().start(0x5ad);
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x2ab), Utility::GetCenterPos(obj()));
    return true;
}

void Custom::setTargetPos(const hel::math::Vector3& pos) {
    mTargetPos = pos;
}

hel::math::Vector3 Custom::getTargetPos() const {
    return mTargetPos;
}

void Custom::setTargetHero(util::ObjRefHandle<hero::Hero> hero) {
    mTargetHero = hero;
}

util::ObjRefHandle<hero::Hero> Custom::getTargetHero() const {
    return mTargetHero;
}

void Custom::reqImageEffect() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x2aa), 1);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::grandlowperbullet
