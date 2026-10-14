#include "scn/step/enemy/searches/StateMove.h"

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
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/searches/Custom.h"
#include "scn/step/enemy/searches/ParamData.h"
#include "scn/step/enemy/searches/StateAttack.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace searches {

StateMove::StateMove(Enemy* enemy) : StateBase(enemy), mDir(Utility::GetDirVecByDirType(*enemy)), mFrame(0), mIsWait(false) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().move().setVelocity(mDir * obj().param().searches().mSpeed);
}

void StateMove::procAnim() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInArea()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

void StateMove::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMove::procFixPos() {
    mFrame++;
    bool isTurn = false;
    if (obj().variation() == 0xa5 && mFrame >= obj().param().searches().mMoveFrame) {
        isTurn = true;
    }
    if (isTurn || obj().mapColl().result().mIsHitFloor || obj().mapColl().result().mIsHitRoof
        || obj().mapColl().result().isHitWall()) {
        mFrame = 0;
        mIsWait = true;
        obj().move().resetVelocity();
    }
    if (mIsWait && mFrame >= obj().param().searches().mWaitFrame) {
        mIsWait = false;
        mFrame = 0;
        mDir = mDir * -1.0f;
        obj().move().setVelocity(mDir * obj().param().searches().mSpeed);
    }
}

}}}}  // namespace scn::step::enemy::searches
