#include "scn/step/enemy/goliathicicle/StateFloorHit.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

StateFloorHit::StateFloorHit(Enemy* enemy) : StateBase(enemy), mFrame(0), mEndFrame(0), mShakeFrame(0) {
    mEndFrame = obj().level() == 0 ? 120 : 180;
    mShakeFrame = mEndFrame - 30;
    obj().footState().setAir();
    obj().nururi().setCanNururi(false);
    obj().move().resetVelocity();
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().soundSE().start(0x37e);
    obj().model().setViewOffset(hel::math::Vector3(0.0f, -0.5f, 0.0f));
}

StateFloorHit::~StateFloorHit() {
    obj().model().resetViewOffset();
}

void StateFloorHit::procAnim() {
    mFrame++;
    if (mFrame == mEndFrame) {
        obj().deadWithEffect();
    } else if (mShakeFrame != 0) {
        mShakeFrame--;
    } else {
        mShakeFrame = 6;
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
}

void StateFloorHit::procMove() {}

void StateFloorHit::procFixPos() {}

}}}}  // namespace scn::step::enemy::goliathicicle
