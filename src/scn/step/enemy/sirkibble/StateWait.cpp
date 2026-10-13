#include "scn/step/enemy/sirkibble/StateWait.h"

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
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/StateCatch.h"
#include "scn/step/enemy/sirkibble/StateJump.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0), mCanJump(true) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    obj().signal().clear();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    mFrame++;
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().signal().isValid()) {
        if (obj().signal().get() == 1) {
            obj().stateChanger().setNextState<StateCatch, Enemy*>(objPtr());
        } else {
            mCanJump = false;
            obj().signal().clear();
        }
    } else if (custom.isNextTurnJump() && mFrame == 30 && mCanJump) {
        obj().signal().set(0);
        custom.setNextTurnJumpInvalid();
        obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
    }
}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sirkibble
