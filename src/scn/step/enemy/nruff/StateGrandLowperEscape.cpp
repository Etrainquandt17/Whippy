#include "scn/step/enemy/nruff/StateGrandLowperEscape.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
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
#include "scn/step/enemy/nruff/ParamData.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

StateGrandLowperEscape::StateGrandLowperEscape(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().nruff();
    obj().footState().setAir();
    obj().model().reqScript(9);
    Vector3 velocity = param.mEscapeVelocity;
    obj().move().setVelocity(velocity);
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().nururi().setValid(false);
}

StateGrandLowperEscape::~StateGrandLowperEscape() {
    obj().nururi().setValid(true);
}

void StateGrandLowperEscape::procAnim() {}

void StateGrandLowperEscape::procMove() {
    const ParamData& param = obj().param().nruff();
    obj().move().airDecelFall(param.mEscapeDecel, param.mEscapeFall);
}

void StateGrandLowperEscape::procFixPos() {
    const ParamData& param = obj().param().nruff();
    if (obj().location().pos().z > param.mEscapeVacuumOffHeight) {
        obj().vacuumReceiver().setIsValid(false);
    }
}

}}}}  // namespace scn::step::enemy::nruff
