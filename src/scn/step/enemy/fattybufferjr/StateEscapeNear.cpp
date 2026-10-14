#include "scn/step/enemy/fattybufferjr/StateEscapeNear.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/fattybufferjr/ParamData.h"

using app::Random;

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
    obj().target().setIsRightDir(Random::RandBool(0.5f));
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

}}}}  // namespace scn::step::enemy::fattybufferjr
