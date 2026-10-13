#include "scn/step/enemy/tick/StateSkip.h"

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
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/tick/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace tick {

StateSkip::StateSkip(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(3);
}

void StateSkip::procMove() {
    const ParamData& param = obj().param().tick();
    mFrame++;
    if (mFrame >= param.mWaitFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            obj().move().setSpeedV(param.mJumpSpeed);
        }
        obj().move().airAccelFall(obj().target().isRightDir(), param.mAccel, param.mFall);
    }
}

void StateSkip::procFixPos() {
    const ParamData& param = obj().param().tick();
    if (mFrame > param.mWaitFrame) {
        if (obj().mapColl().result().isHitWall()) {
            obj().target().setIsRightDir(!obj().target().isRightDir());
        }
        if (obj().mapColl().result().mIsHitFloor && obj().footState().isAir()) {
            obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
        }
    } else if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::tick
