#include "scn/step/enemy/wapod/BrainFly.h"

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
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/StateAppear.h"
#include "scn/step/enemy/wapod/StateRise.h"
#include "scn/step/enemy/wapod/StateStay.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool BrainFly::onRecover() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    u32 variation = custom.wapodpodVariation();
    if (variation == 0xad) {
        obj().stateChanger().setNextState<StateRise, Enemy*>(&obj());
    } else if (variation == 0xae) {
        obj().stateChanger().setNextState<StateStay, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::wapod
