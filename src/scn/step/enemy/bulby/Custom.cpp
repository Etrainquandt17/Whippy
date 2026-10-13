#include "scn/step/enemy/bulby/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/bulby/ParamData.h"
#include "scn/step/map/LandManager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsBuried(true), mX(0), mY(0) {
    mX = static_cast<int>(obj().location().pos().x);
    mY = static_cast<int>(obj().location().pos().y) - 1;
    enemy.model().anim().start(4, true);
}

bool Custom::onDamaged() {
    mIsBuried = false;
    return false;
}

void Custom::onCaptured() {
    mIsBuried = false;
}

void Custom::onProcFixPos() {
    if (mIsBuried) {
        if (hel::math::Math::AbsF32(obj().nururi().getNururiDir().x) >= 1.0f
            || !obj().comp().mapLandManager().native().isExistLand(hel::math::Vector2(static_cast<f32>(mX), static_cast<f32>(mY)))
            || obj().mapColl().result().isHitWall()) {
            mIsBuried = false;
        }
    }
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

bool Custom::isBuried() const {
    return mIsBuried;
}

void Custom::setIsBuried(bool isBuried) {
    mIsBuried = isBuried;
}

}
}
}
}
