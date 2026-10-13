#include "scn/step/enemy/bulby/StateJump.h"

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
#include "scn/step/enemy/bulby/Custom.h"
#include "scn/step/enemy/bulby/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().bulby();
    obj().footState().setAir();
    obj().model().reqScript(9);
    f32 speed;
    if (obj().variation() == 0x64) {
        speed = param.mJumpSpeed;
    } else {
        speed = param.mJumpSpeedAttacker;
    }
    obj().move().setSpeedV(speed);
    obj().objColl().clearBodyColl();
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    obj().objColl().addBodyColl(1, param.mBodyRadius * scale);
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isBuried()) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x375), 0);
        obj().soundSE().start(0x2e6);
    }
}

void StateJump::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(10);
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().bulby();
    obj().move().airDecelFall(param.mDecel, param.mFall);
    if (obj().move().velocity().y < 0.0f) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
