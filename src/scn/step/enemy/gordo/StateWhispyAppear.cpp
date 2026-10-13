#include "scn/step/enemy/gordo/StateWhispyAppear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/whispyapple/StateFall.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

StateWhispyAppear::StateWhispyAppear(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().objColl().bodyColl().setStateXlu();
    obj().model().reqScript(0);
    obj().model().setScale(hel::math::Vector3::ALL_ONE * 0.1f);
}

StateWhispyAppear::~StateWhispyAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateWhispyAppear::procAnim() {
    mFrame++;
    f32 rate = mFrame / 60.0f;
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    obj().model().setScale(hel::math::Vector3::ALL_ONE * hel::math::Math::LinearInterpolation(0.1f, 1.0f, rate));
    if (mFrame == 110) {
        whispyapple::WhispyAppleUtility::ReqFallSE(obj());
        obj().stateChanger().setNextState<whispyapple::StateFall, Enemy*>(objPtr());
    }
}

void StateWhispyAppear::procMove() {}

void StateWhispyAppear::procFixPos() {}

}
}
}
}
