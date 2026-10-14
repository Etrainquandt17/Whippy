#include "scn/step/enemy/leaper/StateFlyAttack.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/leaper/Custom.h"
#include "scn/step/enemy/leaper/ParamData.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

StateFlyAttack::StateFlyAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
    obj().move().resetVelocity();
}

StateFlyAttack::~StateFlyAttack() {}

void StateFlyAttack::procAnim() {
    const ParamData& param = obj().param().leaper();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mShotFrame) {
        custom.reqShot(Vector2::BASIS_X * obj().target().getSign());
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateShootingFly, Enemy*>(objPtr());
    }
}

void StateFlyAttack::procMove() {}

void StateFlyAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::leaper
