#include "scn/step/enemy/bladeknight/StateGrandLowperEscape.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bladeknight/ParamData.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

StateGrandLowperEscape::StateGrandLowperEscape(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().bladeknight();
    obj().footState().setAir();
    obj().model().reqScript(12);
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
    const ParamData& param = obj().param().bladeknight();
    obj().move().airDecelFall(param.mEscapeDecel, param.mEscapeFall);
}

void StateGrandLowperEscape::procFixPos() {
    const ParamData& param = obj().param().bladeknight();
    if (obj().location().pos().z > param.mEscapeVacuumOffHeight) {
        obj().vacuumReceiver().setIsValid(false);
    }
}

}}}}  // namespace scn::step::enemy::bladeknight
