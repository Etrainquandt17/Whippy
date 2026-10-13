#include "scn/step/hero/sword/StateSwordSpin.h"
#include "gobj/Script.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordSpin::StateSwordSpin(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsEnd(false) {
    obj().model().setFixDir(true);
    obj().model().script().start(0x87);
    obj().invincible().setPerm();
}

StateSwordSpin::~StateSwordSpin() {
    if (!mIsEnd) {
        obj().effect()._58.releaseAndVanish();
    }
}

void StateSwordSpin::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        mIsEnd = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSwordSpin::procMove() {
    if (mFrame > 0x28) {
        Utility::MoveDefaultBrakeNoOnIce(obj());
    } else {
        Utility::MoveDefaultNoOnIce(obj());
    }
}

void StateSwordSpin::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::sword
