#include "scn/step/enemy/craby/StateAttack.h"

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
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/craby/Custom.h"
#include "scn/step/enemy/craby/StateWait.h"
#include "scn/step/enemy/craby/StateWalkAround.h"
#include "scn/step/enemy/craby/StateWalkStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mIsLeft(false) {
    obj().footState().setGround();
    obj().move().resetSpeedH();
    f32 x = obj().location().pos().x;
    if (x - Utility::GetNearestPlayerPos(obj()).x <= 0.0f) {
        mIsLeft = true;
        obj().model().reqScript(9);
    } else {
        mIsLeft = false;
        obj().model().reqScript(12);
    }
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (obj().model().isAllEnd()) {
        if (mIsLeft) {
            if (index == 8) {
                obj().model().reqScript(12);
            } else if (index == 11) {
            hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAttackValid(false);
            setNextState();
            }
        } else {
            if (index == 11) {
                obj().model().reqScript(9);
            } else if (index == 8) {
            hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAttackValid(false);
            setNextState();
            }
        }
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).reset();
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateAttack::setNextState() {
    switch (obj().variation()) {
    default:
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        break;
    case 0xd0:
    case 0xd1:
        obj().stateChanger().setNextState<StateWalkStraight, Enemy*>(objPtr());
        break;
    case 0xd2:
        obj().stateChanger().setNextState<StateWalkAround, Enemy*>(objPtr());
        break;
    }
}

}
}
}
}
