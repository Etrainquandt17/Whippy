#include "scn/step/enemy/metalgeneralbit/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), _8(0), _c(0.0f) {}

bool Custom::onInit() {
    obj().culling().setValid(false);
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseCenter(0.7f, 0.7f, 0.5f));
    return false;
}

bool Custom::onHitPointIsZero() {
    if (obj().captureReceiver().isCaptured()) {
        return false;
    }
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        return false;
    }
    obj().deadWithEffect();
    return true;
}

void Custom::onProcFixPos() {}

void Custom::reqRollExp() {
    hel::math::Vector2 pos = obj().location().pos().getXY() + hel::math::Vector2(obj().charaParam()._4);
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().comp().permSoundSE().start(0x3f4);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::metalgeneralbit
