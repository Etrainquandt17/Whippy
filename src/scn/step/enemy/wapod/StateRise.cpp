#include "scn/step/enemy/wapod/StateRise.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/ParamData.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

StateRise::StateRise(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(0);
}

void StateRise::procMove() {
    Vector3 pos = obj().location().pos();
    pos.y += obj().param().wapod().mRiseSpeed;
    obj().location().setPos(pos);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).turn();
}

void StateRise::procFixPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).landHitDead();
}

}}}}  // namespace scn::step::enemy::wapod
