#include "scn/step/enemy/bouncy/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bouncy/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mSpeedH(hel::math::Math::Abs(enemy->move().velocity().x)), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().soundSE().start(0x300);
}

void StateJump::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
}

void StateJump::procMove() {
    if (mFrame > 2) {
        gobj::MoveParamAccel accel = gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f);
        gobj::MoveParamFall fall = gobj::MoveParamFall::Create(obj().param().bouncy().mJumpFallAccel,
                                                               obj().param().bouncy().mJumpFallMaxSpeed,
                                                               obj().param().bouncy().mJumpFallRate);
        obj().move().airAccelFall(obj().target().isRightDir(), accel, fall);
    }
}

void StateJump::procFixPos() {
    if (mFrame > 3 && obj().mapColl().result().mIsHitFloor) {
        obj().brainCtrl().toValid();
    }
    if (obj().mapColl().result().isHitWall()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (Utility::ChkNururiByDir(obj(), 0.0f)) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}
}
}
}
