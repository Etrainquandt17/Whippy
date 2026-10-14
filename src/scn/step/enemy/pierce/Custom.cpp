#include "scn/step/enemy/pierce/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
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
#include "scn/step/enemy/pierce/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mTurnFrame(0) {}

bool Custom::isPlayerInAimArea() {
    const ParamData& param = obj().param().pierce();
    Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    Vector2 pos = obj().location().pos().getXY();
    f32 left = pos.x + param.mAimFront * obj().target().getSign();
    f32 right = pos.x + param.mAimBack;
    f32 top = pos.y + param.mAimV;
    f32 bottom = pos.y - param.mAimV;
    if (left > right) {
        f32 tmp = left;
        left = right;
        right = tmp;
    }
    if (left <= playerPos.x && playerPos.x <= right && bottom <= playerPos.y && playerPos.y <= top) {
        return true;
    }
    return false;
}

void Custom::turnHeroWithTime(u32 time) {
    f32 playerX = Utility::GetNearestPlayerPos(obj()).x;
    bool isRight = playerX > obj().location().pos().x;
    if (isRight != obj().target().isRightDir()) {
        if (++mTurnFrame == time) {
            obj().target().setIsRightDir(isRight);
        }
    } else {
        mTurnFrame = 0;
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::pierce
