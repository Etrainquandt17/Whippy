#include "scn/step/enemy/como/StateCutFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/como/ParamData.h"
#include "scn/step/enemy/como/StateCutLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateCutFall::StateCutFall(Enemy* enemy) : StateBase(enemy), _8(0.0f) {
    obj().footState().setAir();
    obj().move().setSpeedV(obj().param().como().mCutFallSpeed);
    obj().objColl().bodyColl().setStateHitOnly();
    obj().model().reqScript(6);
    obj().soundSE().start(0x2A4);
    obj().objCollReact().setDamageState();
}

StateCutFall::~StateCutFall() {
    obj().move().resetSpeedV();
}

void StateCutFall::procAnim() {}

void StateCutFall::procMove() {
    const ParamData& param = obj().param().como();
    obj().move().airDecelFall(param.mCutFallDecel, param.mCutFallFall);
}

void StateCutFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateCutLanding, Enemy*>(objPtr());
    }
}

}
}
}
}
