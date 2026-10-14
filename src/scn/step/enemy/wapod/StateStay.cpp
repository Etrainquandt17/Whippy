#include "scn/step/enemy/wapod/StateStay.h"

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

StateStay::StateStay(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(0);
}

void StateStay::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 pos = obj().location().pos();
    const ParamData& param = obj().param().wapod();
    u32 level = obj().level();
    if (level > 2) {
        level = 2;
    }
    f32 height = param.mStayHeight[level];
    f32 speed = 0.1f * (height + custom.initPosY() - pos.y);
    if (speed > param.mRiseSpeed) {
        speed = param.mRiseSpeed;
    }
    pos.y += speed;
    obj().location().setPos(pos);
    custom.turn();
}

void StateStay::procFixPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).landHitDead();
}

}}}}  // namespace scn::step::enemy::wapod
