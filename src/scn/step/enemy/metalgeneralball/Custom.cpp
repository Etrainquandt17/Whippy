#include "scn/step/enemy/metalgeneralball/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralball/ParamData.h"
#include "scn/step/enemy/metalgeneralball/StateSpread.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralball {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mMoveCount(0), mIsAlreadyDead(false) {}

bool Custom::onInit() {
    const ParamData& param = obj().param().metalgeneralball();
    obj().culling().setValid(false);
    obj().model().setBaseScale(hel::math::Vector3::ALL_ONE * param.mScale);
    obj().stateChanger().setNextState<StateSpread, Enemy*>(&obj());
    return true;
}

bool Custom::onHitPointIsZero() {
    if (obj().captureReceiver().isCaptured()) {
        return false;
    }
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        mIsAlreadyDead = true;
        return false;
    }
    obj().deadWithEffect();
    return true;
}

void Custom::onProcFixPos() {
    if (obj().captureReceiver().isCaptured()) {
        mIsAlreadyDead = true;
    }
}

void Custom::reqRollExp() {
    hel::math::Vector2 pos = obj().location().pos().getXY() + hel::math::Vector2(obj().charaParam()._4);
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().comp().permSoundSE().start(0x2c8);
}

void Custom::incrementMoveCount() {
    mMoveCount++;
}

u32 Custom::moveCount() {
    return mMoveCount;
}

bool Custom::isAlreadyDead() const {
    return mIsAlreadyDead;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
