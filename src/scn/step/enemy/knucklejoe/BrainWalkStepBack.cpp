#include "scn/step/enemy/knucklejoe/BrainWalkStepBack.h"

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
#include "scn/step/enemy/knucklejoe/Custom.h"
#include "scn/step/enemy/knucklejoe/StateWalkStepBack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

BrainWalkStepBack::BrainWalkStepBack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkStepBack::onStart() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setHitWall(false);
    obj().stateChanger().setNextState<StateWalkStepBack, Enemy*>(&obj());
    return true;
}

bool BrainWalkStepBack::onLanding() {
    return onStart();
}

void BrainWalkStepBack::update() {
    Utility::ChkNururiTurn(obj());
}

}
}
}
}
