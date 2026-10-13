#include "scn/step/hero/sword/StateSwordChoppingHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/sword/StateSwordChopping.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordChoppingHit::StateSwordChoppingHit(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0xD);
    f32 sign = obj().model().isRightDir() ? -1.0f : 1.0f;
    obj().move().setVelocity(hel::math::Vector3(0.05f * sign, 0.275f, 0.0f));
}

StateSwordChoppingHit::~StateSwordChoppingHit() {
}

void StateSwordChoppingHit::procAnim() {
    if (obj().move().velocity().y < 0.0f) {
        if (StateSwordChopping::RetryToChangeState(objPtr()) || common::StateHover::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateSwordChoppingHit::procMove() {
    gobj::MoveParamFall fall = obj().move().velocity().y > 0.0f ? obj().param().common()._9C : obj().param().common()._90;
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), fall);
}

void StateSwordChoppingHit::procFixPos() {
}

}
}
}
}
