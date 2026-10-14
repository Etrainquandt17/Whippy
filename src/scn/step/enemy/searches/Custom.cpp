#include "scn/step/enemy/searches/Custom.h"

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
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/searches/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace searches {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
}

bool Custom::isPlayerInArea() {
    f32 range = obj().param().searches().mAttackRange;
    return Utility::IsHeroInRange(obj(), range, -range, range, -range);
}

bool Custom::searchesDamage() {
    if (obj().damageInfo().smashType() == 0) {
        Vector2 pos = obj().location().pos().getXY();
        weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 2, static_cast<ostop::Flag>(4), pos, pos, Vector2(0.0f, 0.0f),
                          obj().objColl().owner());
        obj().comp().weaponManager().request(desc);
        obj().comp().permSoundSE().start(0x50e);
        obj().deadIndependent();
        return true;
    }
    return false;
}

bool Custom::onDamaged() {
    return searchesDamage();
}

bool Custom::onHitPointIsZero() {
    return searchesDamage();
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::searches
