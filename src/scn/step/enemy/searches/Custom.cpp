#include "scn/step/enemy/searches/Custom.h"

#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/searches/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

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
