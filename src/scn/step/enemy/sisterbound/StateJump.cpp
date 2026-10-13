#include "scn/step/enemy/sisterbound/StateJump.h"

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
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    mSpeedH = hel::math::Math::AbsF32(obj().move().velocity().x);
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().model().anim().setFrameRate(obj().param().sisterbound().mLandingFrameRate);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    if (obj().move().velocity().y <= 0.0f) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().sisterbound();
    const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f);
    obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mJumpFall);
}

void StateJump::procFixPos() {
    if (obj().variation() != 0x3d) {
        Utility::ChkNururiTurn(obj());
        if (obj().mapColl().result()._2) {
            obj().target().invert();
        }
    }
}

}
}
}
}
