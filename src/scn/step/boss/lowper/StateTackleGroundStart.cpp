#include "scn/step/boss/lowper/StateTackleGroundStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateTackleGroundStart::StateTackleGroundStart(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Vector3 pos;
    f32 baseX = obj().basePos().x;
    f32 sign = Math::SignF32(obj().location().pos().x - baseX);
    pos.x = obj().basePos().x + 0.5f * sign * param._34;
    pos.y = param._38 + obj().basePos().y;
    custom.waftMoveCtrl().setMoveIntpRate(0.075f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
    obj().model().reqScript(8);
}

StateTackleGroundStart::~StateTackleGroundStart() {}

void StateTackleGroundStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleGroundStart::procMove() {}

void StateTackleGroundStart::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
