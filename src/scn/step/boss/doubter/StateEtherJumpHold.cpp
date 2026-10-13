#include "scn/step/boss/doubter/StateEtherJumpHold.h"

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
#include "scn/step/boss/doubter/StateEtherJumpFall.h"
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

StateEtherJumpHold::StateEtherJumpHold(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartX(boss->location().pos().x), mGoalX(boss->location().pos().x) {
    obj().footState().setAir();
    obj().guard().setType(static_cast<GuardType>(2));
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    obj().move().resetVelocity();
    mGoalX = Utility::GetHatedHeroPos(obj()).x;
}

StateEtherJumpHold::~StateEtherJumpHold() {}

void StateEtherJumpHold::procAnim() {
    mCount++;
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateEtherJumpFall, Boss*>(objPtr());
    }
}

void StateEtherJumpHold::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector3 pos = obj().location().pos();
    pos.x = t * (mGoalX - mStartX) + mStartX;
    obj().location().setPos(pos);
}

void StateEtherJumpHold::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
