#include "scn/step/enemy/dubiorjr/StateBack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/dubiorjr/ParamData.h"

using hel::math::Direction3;

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

StateBack::StateBack(Enemy* enemy, f32 rot) : StateBase(enemy) {
    const ParamData& param = obj().param().dubiorjr();
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().model().rotCtrl().setRotVTarget(rot * obj().target().getSign());
    obj().brainCtrl().toValid();
    Direction3 dir = obj().target().getDirection3();
    dir.mFront.rotate(dir.mLeft, 0.017453292f * -rot);
    dir.restructFrontLeft();
    obj().move().setVelocity(dir.mFront * -param.mBackSpeed);
}

StateBack::~StateBack() {}

void StateBack::procAnim() {
    const ParamData& param = obj().param().dubiorjr();
}

void StateBack::procMove() {
    const ParamData& param = obj().param().dubiorjr();
    obj().move().groundDecel(param.mBackDecel);
}

void StateBack::procFixPos() {}

}}}}  // namespace scn::step::enemy::dubiorjr
