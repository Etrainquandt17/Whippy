#include "scn/step/enemy/bladeknight/Custom.h"

#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/map/LandManager.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mWalkFlag(false) {}

void Custom::setupSuperEnemyEffect() {
    hel::math::Vector3 center = obj().location().toCenter();
    obj().effect().super().requestN(effect::KIND_132, 0, center);
    obj().effect().super().requestN(static_cast<effect::Kind>(0x526), 1);
}

void Custom::walkFlagOn() {
    mWalkFlag = true;
}

bool Custom::backStepCliffChk() {
    hel::math::Vector3 p = obj().location().pos();
    hel::math::Vector2 pos(p.x, p.y);
    pos.y += 0.05f;
    hel::math::Vector2 check = pos + hel::math::Vector2(0.0f, -0.5f);
    if (!obj().comp().mapLandManager().native().isExistLand(check) && !obj().comp().mapLandManager().native().isExistMoveLand(check)) {
        return false;
    }
    pos.x += 0.4f * -obj().target().getSign();
    if (obj().comp().mapLandManager().native().isExistLand(pos) || obj().comp().mapLandManager().native().isExistMoveLand(pos)) {
        return false;
    }
    pos.y -= 0.5f;
    if (obj().comp().mapLandManager().native().isExistLand(pos) || obj().comp().mapLandManager().native().isExistMoveLand(pos)) {
        return false;
    }
    return true;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::bladeknight
