#include "scn/step/enemy/goliathiceball/StateWallHit.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/goliathiceball/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

StateWallHit::StateWallHit(Enemy* enemy) : StateBase(enemy), mFrame(0), mEndFrame(0) {
    mEndFrame = obj().variation() == 0x176 ? 15 : 60;
    obj().footState().setAir();
    obj().nururi().setCanNururi(false);
    obj().move().resetVelocity();
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().soundSE().start(0x381);
}

StateWallHit::~StateWallHit() {}

void StateWallHit::procAnim() {
    mFrame++;
    if (mFrame == mEndFrame) {
        if (obj().variation() == 0x176) {
            DynamicCastToRef<Custom, ICustom>(obj().custom()).reqExplode();
        }
        obj().deadWithEffect();
    }
}

void StateWallHit::procMove() {}

void StateWallHit::procFixPos() {}

}}}}  // namespace scn::step::enemy::goliathiceball
