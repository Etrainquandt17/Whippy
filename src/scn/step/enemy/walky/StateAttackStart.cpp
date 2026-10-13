#include "scn/step/enemy/walky/StateAttackStart.h"

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
#include "scn/step/enemy/walky/ParamData.h"
#include "scn/step/enemy/walky/StateAttack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

StateAttackStart::StateAttackStart(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mIsRightDir(obj().target().isRightDir()), _d(false) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    obj().model().rotCtrl().setRotHIntpRate(0.2f);
}

StateAttackStart::~StateAttackStart() {
    obj().model().rotCtrl().setRotHIntpRate(0.1f);
}

void StateAttackStart::procAnim() {
    mFrame++;
    if (mFrame >= obj().param().walky().mAttackTurnFrame + obj().param().walky().mAttackWaitFrame) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    } else if (mFrame == obj().param().walky().mAttackTurnFrame) {
        Utility::TurnHero(obj());
        if (mIsRightDir == obj().target().isRightDir()) {
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    }
}

void StateAttackStart::procMove() {}

void StateAttackStart::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walky
