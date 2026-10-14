#include "scn/step/boss/doubter/StatePunch.h"

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
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StatePunch::StatePunch(Boss* boss, ScriptKind kind) : StateBase(boss), mDecel(boss->param().doubter().mPunch._4) {
    obj().footState().setGround();
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(kind);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(4));
}

StatePunch::~StatePunch() {}

void StatePunch::procAnim() {
    const PunchParam& punch = Utility::IsVariationExtra(obj()) ? obj().param().doubter().mPunchExtra : obj().param().doubter().mPunch;
    if (obj().scriptTrigger().get(1)) {
        obj().move().setSpeedH(punch._0 * obj().target().getSign());
        mDecel = punch._4;
    }
    if (obj().scriptTrigger().get(2)) {
        obj().move().setSpeedH(punch._8 * obj().target().getSign());
        mDecel = punch._C;
    }
    if (obj().scriptTrigger().get(3)) {
        obj().move().setSpeedH(punch._10 * obj().target().getSign());
        mDecel = punch._14;
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePunch::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(mDecel));
}

void StatePunch::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
