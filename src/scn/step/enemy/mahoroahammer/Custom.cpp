#include "scn/step/enemy/mahoroahammer/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/mahoroahammer/StateBound.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onRecover() {
    obj().stateChanger().setNextState<StateBound, Enemy*, hel::math::Vector2>(&obj(), hel::math::Vector2::ZERO);
    return true;
}

void Custom::setupSuperEnemyEffect() {
    obj().effect().super().requestN(static_cast<effect::Kind>(0x132), 0, obj().location().toCenter());
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::mahoroahammer
