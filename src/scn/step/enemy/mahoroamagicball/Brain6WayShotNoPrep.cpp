#include "scn/step/enemy/mahoroamagicball/Brain6WayShotNoPrep.h"

#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/State6WayPreShot.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

Brain6WayShotNoPrep::Brain6WayShotNoPrep(Enemy& enemy) : BrainBase(enemy) {}

bool Brain6WayShotNoPrep::onStart() {
    obj().stateChanger().setNextState<State6WayPreShot, Enemy*, Vector3, f32, f32>(
        &obj(), obj().location().pos(), 0.0f, 60.0f * static_cast<f32>(obj().level()));
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
