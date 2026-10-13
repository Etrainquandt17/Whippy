#include "scn/step/enemy/mahoroamagicball/Brain6WayShotNoPrep.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"
#include "scn/step/enemy/mahoroamagicball/ParamData.h"
#include "scn/step/enemy/mahoroamagicball/State6WayPreShot.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

Brain6WayShotNoPrep::Brain6WayShotNoPrep(Enemy& enemy) : BrainBase(enemy) {}

bool Brain6WayShotNoPrep::onStart() {
    obj().stateChanger().setNextState<State6WayPreShot, Enemy*, hel::math::Vector3, f32, f32>(
        &obj(), obj().location().pos(), 0.0f, 60.0f * static_cast<f32>(obj().level()));
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
