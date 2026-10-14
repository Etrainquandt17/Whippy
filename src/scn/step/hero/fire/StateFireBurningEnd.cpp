#include "scn/step/hero/fire/StateFireBurningEnd.h"
#include "gobj/Move.h"
#include "scn/step/hero/FireParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

StateFireBurningEnd::StateFireBurningEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0xB3);
    obj().move().resetSpeedV();
    obj().move().setSpeedH(obj().move().velocity().x * obj().param().fire()._8C);
}

StateFireBurningEnd::~StateFireBurningEnd() {
}

void StateFireBurningEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateFireBurningEnd::procMove() {
    Utility::MoveDefaultNoOnIce(obj());
}

void StateFireBurningEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::fire
