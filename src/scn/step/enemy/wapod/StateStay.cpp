#include "scn/step/enemy/wapod/StateStay.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

StateStay::StateStay(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(0);
}

void StateStay::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    hel::math::Vector3 pos = obj().location().pos();
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
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).landHitDead();
}

}}}}  // namespace scn::step::enemy::wapod
