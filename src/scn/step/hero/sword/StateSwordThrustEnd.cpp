#include "scn/step/hero/sword/StateSwordThrustEnd.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordThrustEnd::StateSwordThrustEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0x7A);
}

StateSwordThrustEnd::~StateSwordThrustEnd() {
}

void StateSwordThrustEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSwordThrustEnd::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateSwordThrustEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::sword
