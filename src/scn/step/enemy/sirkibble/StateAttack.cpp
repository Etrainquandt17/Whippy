#include "scn/step/enemy/sirkibble/StateAttack.h"

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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/ParamData.h"
#include "scn/step/enemy/sirkibble/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(7);
    custom.chkNextTurnJump();
    if (custom.isNextTurnJump()) {
        obj().target().invert();
    }
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().sirkibble();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mAttackShotFrame) {
        custom.reqWeapon();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateAttack::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateAttack::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sirkibble
