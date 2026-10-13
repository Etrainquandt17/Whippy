#include "scn/step/hero/leaf/StateSpread.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

StateSpread::StateSpread(Hero* hero)
    : StateBase(hero)
    , mIsEnd(false) {
    obj().model().script().start(0x9D);
    obj().move().resetVelocity();
    obj().knockback().setIsValid(false);
}

StateSpread::~StateSpread() {
    if (!mIsEnd) {
        obj().effect()._58.releaseAndVanish();
    }
}

void StateSpread::procAnim() {
    if (obj().model().isAllEnd()) {
        mIsEnd = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSpread::procMove() {
}

void StateSpread::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
