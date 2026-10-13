#include "scn/step/enemy/bouncy/StateGrandLowperAppear.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

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
        f32 rotY = 720.0f * (1.0f - hel::math::Math::CosDegF(90.0f * rate));
        hel::math::Vector3 rot(90.0f * (1.0f - hel::math::Math::CosDegF(90.0f * rate)), rotY, 0.0f);
        Utility::SetCustomMtxRotate(obj(), rot);
    }
}

void StateGrandLowperAppear::procMove() {
    mAlgorithm.procMove();
}

void StateGrandLowperAppear::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::bouncy
