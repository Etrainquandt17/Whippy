#include "scn/step/enemy/mahoroahammer/Custom.h"

#include "hel/math/Vector2.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroahammer/StateBound.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onRecover() {
    obj().stateChanger().setNextState<StateBound, Enemy*, Vector2>(&obj(), Vector2::ZERO);
    return true;
}

void Custom::setupSuperEnemyEffect() {
    obj().effect().super().requestN(static_cast<effect::Kind>(0x132), 0, obj().location().toCenter());
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::mahoroahammer
