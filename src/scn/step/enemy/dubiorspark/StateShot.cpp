#include "scn/step/enemy/dubiorspark/StateShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/dubiorspark/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorspark {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().dubiorspark();
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().worldCage().setIsValid(true);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4ed), 0);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {}

void StateShot::procMove() {
    const ParamData& param = obj().param().dubiorspark();
    obj().move().decel(param.mDecel);
}

void StateShot::procFixPos() {
    const ParamData& param = obj().param().dubiorspark();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit() || obj().worldCage().isCorrected()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::dubiorspark
