#include "scn/step/enemy/sisterbound/StateJumpStart.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
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
#include "scn/step/enemy/sisterbound/ParamData.h"
#include "scn/step/enemy/sisterbound/StateFall.h"
#include "scn/step/enemy/sisterbound/StateJump.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

StateJumpStart::StateJumpStart(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    mSpeedH = hel::math::Math::AbsF32(obj().move().velocity().x);
    obj().footState().setGround();
    obj().model().reqScript(8);
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
    }
}

void StateJumpStart::procMove() {
    const ParamData& param = obj().param().sisterbound();
    mFrame++;
    if (obj().model().anim().frame() >= static_cast<f32>(param.mJumpFrame)) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            obj().move().setSpeedV(param.mJumpSpeed);
            obj().soundSE().start(0x301);
        }
        const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f);
        obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mJumpFall);
    }
}

void StateJumpStart::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
