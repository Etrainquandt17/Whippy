#include "scn/step/enemy/scarfy/StateGrandLowperAppear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateGrandLowperAppear::StateGrandLowperAppear(Enemy* enemy) : StateBase(enemy), mAlgorithm(*enemy) {
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(11);
    obj().move().resetVelocity();
}

StateGrandLowperAppear::~StateGrandLowperAppear() {
    obj().objColl().bodyColl().setStateNormal();
    obj().model().unsetCustomMtx();
}

void StateGrandLowperAppear::procAnim() {
    mAlgorithm.procAnim();
    if (!mAlgorithm.isHoldEnd()) {
        f32 rate = mAlgorithm.getHoldFrameRate();
        hel::math::Vector3 rot(-720.0f * (1.0f - hel::math::Math::CosDegF(90.0f * rate)), 0.0f, 0.0f);
        Utility::SetCustomMtxRotate(obj(), rot);
    } else {
        obj().stateChanger().setNextState<StateFaceChange, Enemy*>(objPtr());
    }
}

void StateGrandLowperAppear::procMove() {}

void StateGrandLowperAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::scarfy
