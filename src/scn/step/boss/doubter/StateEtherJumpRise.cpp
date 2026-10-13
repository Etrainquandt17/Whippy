#include "scn/step/boss/doubter/StateEtherJumpRise.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateEtherJumpHold.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateEtherJumpRise::StateEtherJumpRise(Boss* boss, u32 frame) : StateBase(boss), mFrame(frame) {
    obj().footState().setAir();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(33);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    obj().move().resetVelocity();
    obj().move().setSpeedV(obj().param().doubter()._154);
}

StateEtherJumpRise::~StateEtherJumpRise() {}

void StateEtherJumpRise::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateEtherJumpRise::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().airDecelFall(param._15C, param._160);
}

void StateEtherJumpRise::procFixPos() {
    const Param& param = obj().param().doubter();
    f32 height = param._158 + obj().basePos().y;
    if (obj().location().pos().y > height) {
        obj().stateChanger().setNextState<StateEtherJumpHold, Boss*, u32>(objPtr(), mFrame);
    }
}

}
}
}
}
