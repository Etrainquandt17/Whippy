#include "scn/step/enemy/owgulf/StateFlyStraight.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/owgulf/ParamData.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

StateFlyStraight::StateFlyStraight(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
    obj().move().resetSpeedV();
}

void StateFlyStraight::procMove() {
    const ParamData& param = obj().param().owgulf();
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(param.mSpeed, param.mSpeed * 0.1f, 0.001f));
}

void StateFlyStraight::procFixPos() {
    if (obj().mapColl().result()._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    } else if (Math::Abs(obj().nururi().getNururiDir().x) >= 0.1f) {
        obj().target().setIsRightDir(obj().nururi().getNururiDir().x > 0.0f);
    }
}

}}}}  // namespace scn::step::enemy::owgulf
