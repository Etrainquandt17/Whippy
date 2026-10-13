#include "scn/step/boss/doubter/StateJugglingAttack2.h"

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

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJugglingAttack2::StateJugglingAttack2(Boss* boss) : StateBase(boss), _8(0.0f) {
    obj().footState().setAir();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    custom.jugglingCtrl().signalAllEnemyPrepare2();
    custom.jugglingCtrl().inactivateEnf();
    obj().model().reqScript(30);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(1));
}

StateJugglingAttack2::~StateJugglingAttack2() {}

void StateJugglingAttack2::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.jugglingCtrl().signalAllEnemyShot2();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateJugglingAttack2::procMove() {
    obj().location().setPos(hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).waftPositionCtrl().getNextPos());
}

void StateJugglingAttack2::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
