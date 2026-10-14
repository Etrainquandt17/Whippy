#include "scn/step/enemy/squishy/Custom.h"

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
#include "scn/step/enemy/squishy/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), _8(false), _9(false), mIsJumpFromWater(false) {}

bool Custom::onInit() {
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

bool Custom::onOutWater() {
    return onInWater();
}

bool Custom::isJumpFromWater() {
    return mIsJumpFromWater;
}

void Custom::setJumpFromWater(bool flag) {
    mIsJumpFromWater = flag;
}

bool Custom::isInWater(bool flag) {
    const ParamData& param = obj().param().squishy();
    Vector3 pos = obj().location().pos();
    if (!flag) {
        pos.y += param.mWaterCheckOffsetY;
    }
    return Utility::IsWaterGrid(obj(), pos.x, pos.y);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::squishy
