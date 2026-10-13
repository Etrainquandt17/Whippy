#include "scn/step/enemy/foley/StateMove.h"

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
#include "scn/step/enemy/foley/ParamData.h"
#include "scn/step/enemy/foley/StateAttack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

StateMove::StateMove(Enemy* enemy) : StateBase(enemy), mIsReady(false) {
    const ParamData& param = obj().param().foley();
    switch (obj().level()) {
    case 0:
        mAccel = param.mMoveAccel[0];
        break;
    case 1:
        mAccel = param.mMoveAccel[1];
        break;
    default:
        mAccel = param.mMoveAccel[2];
        break;
    }
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateMove::~StateMove() {}

void StateMove::procAnim() {
    const ParamData& param = obj().param().foley();
    if (2.0f == obj().model().anim().frame()) {
        mIsReady = true;
    }
    if (mIsReady) {
        if (Utility::IsHeroInRange(obj(), 0.0f, -param.mRangeH, -param.mMoveRangeV, param.mMoveRangeV)) {
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    }
}

void StateMove::procMove() {
    obj().move().airAccelFall(obj().target().isRightDir(), mAccel, gobj::MoveParamFall::Zero());
}

void StateMove::procFixPos() {
    if (obj().mapColl().result().isHitWallFront()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::foley
