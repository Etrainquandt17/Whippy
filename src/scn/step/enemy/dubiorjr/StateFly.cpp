#include "scn/step/enemy/dubiorjr/StateFly.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/dubiorjr/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

StateFly::StateFly(Enemy* enemy, f32 rot) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().model().rotCtrl().setRotVTarget(rot * obj().target().getSign());
    obj().brainCtrl().toValid();
}

StateFly::~StateFly() {}

void StateFly::procAnim() {}

void StateFly::procMove() {
    const ParamData& param = obj().param().dubiorjr();
    obj().move().decel(param.mDecel);
}

void StateFly::procFixPos() {}

}}}}  // namespace scn::step::enemy::dubiorjr
