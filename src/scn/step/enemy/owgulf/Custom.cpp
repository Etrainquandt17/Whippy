#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/owgulf/Custom.h"

#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

void Custom::shot(Vector3 pos, Vector3 velocity, weapon::owgulffeather::VariationKind kind) {
    obj().soundSE().start(0x559);
    weapon::Desc desc(static_cast<weapon::Kind>(0x35), kind, static_cast<ostop::Flag>(4), pos.getXY(), velocity.getXY(),
                      obj().objColl().owner());
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        weapon->move().setVelocity(velocity);
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::owgulf
