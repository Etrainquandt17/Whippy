#include "scn/step/enemy/fattybufferjr/StateEscapeNear.h"

#include "app/Random.h"
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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/fattybufferjr/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

StateEscapeNear::StateEscapeNear(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().fattybufferjr();
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().setVelocity(param.mEscapeVelocity);
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().target().setIsRightDir(app::Random::RandBool(0.5f));
}

void StateEscapeNear::procAnim() {}

void StateEscapeNear::procMove() {
    const ParamData& param = obj().param().fattybufferjr();
    obj().move().airDecelFall(param.mEscape.mDecel, param.mEscape.mFall);
}

void StateEscapeNear::procFixPos() {
    f32 endZ = obj().param().fattybufferjr().mEscapeEndZ;
    if (obj().location().pos().z > endZ) {
        obj().vacuumReceiver().setIsValid(false);
    }
}

}
}
}
}
