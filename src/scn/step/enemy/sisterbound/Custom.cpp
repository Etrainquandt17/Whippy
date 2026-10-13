#include "scn/step/enemy/sisterbound/Custom.h"

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
#include "scn/step/enemy/sisterbound/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    const ParamData& param = obj().param().sisterbound();
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(1, param.mBodyRadius, param.mBodyOffset);
    obj().objColl().addBodyColl(0, param.mHeadRadius, param.mHeadOffset, param.mHeadOffset2);
    return false;
}

bool Custom::onDamaged() {
    obj().soundSE().stop();
    return false;
}

bool Custom::isChangeDir() {
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    bool result = false;
    if ((pos.x - playerPos.x < 0.0f && !obj().target().isRightDir()) || (pos.x - playerPos.x > 0.0f && obj().target().isRightDir())) {
        result = true;
    }
    return result;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
