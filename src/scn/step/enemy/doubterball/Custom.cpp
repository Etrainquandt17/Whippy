#include "scn/step/enemy/doubterball/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
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
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace doubterball {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    if (obj().kind() == 0x6d) {
        f32 scale = 0.5f * obj().model().getTotalScale().x;
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x119), 0, scale);
    }
    return false;
}

bool Custom::onDamaged() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 0xd) {
        return false;
    }
    return true;
}

void Custom::onDead() {
    if (obj().kind() == 0x6d) {
        obj().effect().normal().release();
    }
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x113), Utility::GetCenterPos(obj()));
    obj().comp().permSoundSE().start(0x32e);
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::doubterball
