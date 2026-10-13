#include "scn/step/boss/doubter/StateJumpCenterStart.h"

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
#include "scn/step/boss/doubter/StateJumpCenter.h"
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

StateJumpCenterStart::StateJumpCenterStart(Boss* boss, f32 speed, u32 kind) : StateBase(boss), mSpeed(speed), mKind(kind) {
    obj().footState().setGround();
    obj().model().reqScript(9);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateJumpCenterStart::~StateJumpCenterStart() {}

void StateJumpCenterStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpCenter, Boss*, f32, u32>(objPtr(), mSpeed, mKind);
    }
}

void StateJumpCenterStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateJumpCenterStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
