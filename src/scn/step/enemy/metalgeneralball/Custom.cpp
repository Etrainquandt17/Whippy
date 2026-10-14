#include "scn/step/enemy/metalgeneralball/Custom.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/metalgeneralball/ParamData.h"
#include "scn/step/enemy/metalgeneralball/StateSpread.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralball {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mMoveCount(0), mIsAlreadyDead(false) {}

bool Custom::onInit() {
    const ParamData& param = obj().param().metalgeneralball();
    obj().culling().setValid(false);
    obj().model().setBaseScale(Vector3::ALL_ONE * param.mScale);
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
    Vector2 pos = obj().location().pos().getXY() + Vector2(obj().charaParam()._4);
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(8), pos, Vector2::ZERO,
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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::metalgeneralball
