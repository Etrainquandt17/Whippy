#include "scn/step/hero/highjump/StateRoofHit.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/HighjumpParam.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

StateRoofHit::StateRoofHit(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().invincible().setPerm();
    f32 maxSpeedH = obj().param().highjump()._DC;
    f32 maxSpeedV = obj().param().highjump()._E0;
    hel::math::Vector2 velocity = obj().move().velocity().getXY();
    if (hel::math::Math::AbsF32(velocity.x) > maxSpeedH) {
        obj().move().setSpeedH(maxSpeedH * obj().target().getSign());
    }
    if (velocity.y > maxSpeedV) {
        obj().move().setSpeedV(maxSpeedV);
    }
    obj().model().script().start(0xFE);
}

StateRoofHit::~StateRoofHit() {
}

void StateRoofHit::procAnim() {
    const HighjumpParam& param = obj().param().highjump();
    if (obj().model().scriptTrigger().get(0)) {
        obj().abilityManager().setActionInterval(param._E4);
        obj().invincible().set(param._E8);
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateRoofHit::procMove() {
    const HighjumpParam& param = obj().param().highjump();
    obj().move().airDecelFall(param._EC, param._F0);
}

void StateRoofHit::procFixPos() {
}

}}}}  // namespace scn::step::hero::highjump
