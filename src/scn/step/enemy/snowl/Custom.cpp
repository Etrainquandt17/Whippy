#include "scn/step/enemy/snowl/Custom.h"

#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/snowl/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace snowl {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x1a7));
    return false;
}

void Custom::requestBall() {
    Vector2 pos = obj().location().pos().getXY();
    weapon::Desc desc(static_cast<weapon::Kind>(0x43), 0, static_cast<ostop::Flag>(4), pos, pos, obj().param().snowl().mBallVelocity,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::snowl
