#include "scn/step/enemy/gordo/StateGrandLowperAppear.h"

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

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

StateGrandLowperAppear::StateGrandLowperAppear(Enemy* enemy) : StateBase(enemy), mAlgorithm(*enemy) {
    obj().footState().setAir();
    obj().objColl().bodyColl().setStateXlu();
    obj().model().reqScript(1);
    obj().move().resetVelocity();
    obj().model().setScale(Vector3::ALL_ONE * 0.1f);
}

StateGrandLowperAppear::~StateGrandLowperAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateGrandLowperAppear::procAnim() {
    mAlgorithm.procAnim();
    if (!mAlgorithm.isHoldEnd()) {
        f32 rate = 1.0f - mAlgorithm.getHoldFrameRate();
        obj().model().setScale(Vector3::ALL_ONE * Math::LinearInterpolation(0.1f, 1.0f, rate));
    } else {
        whispyapple::WhispyAppleUtility::ReqFallSE(obj());
        obj().stateChanger().setNextState<whispyapple::StateFall, Enemy*, int, bool>(objPtr(), 1, true);
    }
}

void StateGrandLowperAppear::procMove() {}

void StateGrandLowperAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::gordo
