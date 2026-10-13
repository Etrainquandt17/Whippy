#include "scn/step/enemy/blipper/StateFattyBufferEscapeNear.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/blipper/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateFattyBufferEscapeNear::StateFattyBufferEscapeNear(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().blipper();
    obj().footState().setAir();
    obj().model().reqScript(0);
    hel::math::Vector3 velocity = param.mFattyBufferEscapeVelocity;
    obj().move().setVelocity(velocity);
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().target().setIsRightDir(app::Random::RandBool(0.5f));
    obj().nururi().setCanNururi(false);
}

void StateFattyBufferEscapeNear::procAnim() {}

void StateFattyBufferEscapeNear::procMove() {
    const ParamData& param = obj().param().blipper();
    obj().move().airDecelFall(param.mFattyBufferDecel, param.mFattyBufferFall);
}

void StateFattyBufferEscapeNear::procFixPos() {
    const ParamData& param = obj().param().blipper();
    if (obj().location().pos().z > param.mFattyBufferEscapeVacuumOffHeight) {
        obj().vacuumReceiver().setIsValid(false);
    }
}

}
}
}
}
