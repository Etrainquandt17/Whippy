#include "scn/step/enemy/degout/Custom.h"

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
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace degout {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsChaseFlag(false), mIsFirstChase(false) {}

bool Custom::onInit() {
    return false;
}

bool Custom::onDamaged() {
    mIsFirstChase = true;
    if (obj().variation() == 0x7f) {
        mIsChaseFlag = true;
    }
    return false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setChaseFlag(bool flag) {
    mIsChaseFlag = flag;
}

bool Custom::isChaseFlag() const {
    return mIsChaseFlag;
}

void Custom::setFirstChase(bool flag) {
    mIsFirstChase = flag;
}

bool Custom::isFirstChase() const {
    return mIsFirstChase;
}

}}}}  // namespace scn::step::enemy::degout
