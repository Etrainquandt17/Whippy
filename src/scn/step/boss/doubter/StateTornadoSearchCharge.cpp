#include "scn/step/boss/doubter/StateTornadoSearchCharge.h"

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
#include "scn/step/boss/doubter/StateTornadoSearch.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateTornadoSearchCharge::StateTornadoSearchCharge(Boss* boss, u32 frame, u32 searchFrame, f32 rate)
    : StateBase(boss), mFrame(frame), mSearchFrame(searchFrame), mRate(rate), mCount(0), mDecel(0.0f) {
    const Param& param = obj().param().doubter();
    obj().footState().setAir();
    Utility::TurnHatedHero(obj());
    f32 speed = param._C8 * obj().target().getSign();
    obj().move().setSpeedH(speed);
    obj().move().resetSpeedV();
    if (mFrame != 0) {
        mDecel = hel::math::Math::AbsF32(speed) / static_cast<f32>(mFrame);
    }
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(14);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    obj().soundSE().loop().start(0x336);
}

StateTornadoSearchCharge::~StateTornadoSearchCharge() {}

void StateTornadoSearchCharge::procAnim() {
    mCount++;
    if (mCount >= mFrame) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<StateTornadoSearch, Boss*, u32, f32>(objPtr(), mSearchFrame, mRate);
    }
}

void StateTornadoSearchCharge::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(mDecel), gobj::MoveParamFall::Zero());
}

void StateTornadoSearchCharge::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
