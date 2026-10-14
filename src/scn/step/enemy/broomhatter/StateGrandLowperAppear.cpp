#include "scn/step/enemy/broomhatter/StateGrandLowperAppear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateLanding.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

StateGrandLowperAppear::StateGrandLowperAppear(Enemy* enemy) : StateBase(enemy), mAlgorithm(*enemy) {
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(1);
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
        Vector3 rot(-720.0f * (1.0f - Math::CosDegF(90.0f * rate)), 0.0f, 0.0f);
        Utility::SetCustomMtxRotate(obj(), rot);
    }
}

void StateGrandLowperAppear::procMove() {
    mAlgorithm.procMove();
}

void StateGrandLowperAppear::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::broomhatter
