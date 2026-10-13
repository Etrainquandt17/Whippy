#include "scn/step/enemy/babut/StateTakeOff.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/babut/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateTakeOff::StateTakeOff(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().babut();
    obj().footState().setAir();
    obj().model().reqScript(7);
    Utility::TurnHero(obj());
    obj().move().setSpeedV(-param.mTakeOffHeight / param.mTakeOffFrame);
}

void StateTakeOff::procAnim() {
    const ParamData& param = obj().param().babut();
    mFrame++;
    if (mFrame == param.mTakeOffSoundFrame) {
        obj().soundSEState().start(0x307);
    } else if (mFrame >= static_cast<u32>(param.mTakeOffFrame)) {
        obj().move().resetVelocity();
        obj().brainCtrl().toValid();
    }
}

void StateTakeOff::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

}
}
}
}
