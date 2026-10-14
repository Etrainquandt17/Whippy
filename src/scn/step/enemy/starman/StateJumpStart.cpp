#include "scn/step/enemy/starman/StateJumpStart.h"

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
#include "scn/step/enemy/starman/Custom.h"
#include "scn/step/enemy/starman/ParamData.h"
#include "scn/step/enemy/starman/StateFall.h"
#include "scn/step/enemy/starman/StateFly.h"
#include "scn/step/enemy/starman/StateJump.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace starman {

StateJumpStart::StateJumpStart(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().starman();
    obj().move().resetSpeedH();
    switch (obj().variation()) {
    default:
        obj().model().reqScript(7);
        break;
    case 0x59: {
        f32 y = obj().location().pos().y;
        if (param.mHighJumpRange + Utility::GetNearestPlayerPos(obj()).y > y) {
            obj().model().reqScript(9);
            obj().model().rotCtrl().setRotHTarget(0.0f);
        } else {
            obj().model().reqScript(7);
        }
        break;
    }
    case 0x5e:
        obj().model().reqScript(9);
        break;
    }
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    const ParamData& param = obj().param().starman();
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (obj().model().isAllEnd()) {
        if (index == 6 && mFrame == param.mJumpStartFrame) {
            DynamicCastToRef<Custom, ICustom>(obj().custom()).setHighJumpMode(false);
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        } else if (index == 8 && mFrame == param.mHighJumpStartFrame) {
            if (obj().variation() == 0x5e) {
                obj().effect().normal().requestP(static_cast<effect::Kind>(0x124), obj().location().pos());
                obj().stateChanger().setNextState<StateFly, Enemy*>(objPtr());
            } else {
                DynamicCastToRef<Custom, ICustom>(obj().custom()).setHighJumpMode(true);
                obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
            }
        } else {
            mFrame++;
        }
    }
}

void StateJumpStart::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::starman
