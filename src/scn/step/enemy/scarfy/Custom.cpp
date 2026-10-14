#include "scn/step/enemy/scarfy/Custom.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsAnger(false), mIsFaceChanged(false) {
    obj().nururi().changeSetting(Vector2(0.0f, 0.0f), 2.0f * obj().charaParam()._2c, 2.0f * obj().charaParam()._2c,
                                 nururi::MODE_1);
}

bool Custom::scarfyDamage() {
    int smashType = obj().damageInfo().data().mSmashType;
    if (mIsAnger == true && smashType == 0) {
        Vector2 pos = obj().location().pos().getXY();
        Vector2 genPos = pos;
        weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 2, static_cast<ostop::Flag>(4), genPos, pos,
                          Vector2(0.0f, 0.0f), obj().objColl().owner());
        obj().comp().weaponManager().request(desc);
        obj().comp().permSoundSE().start(0x2c8);
        obj().dead();
        return true;
    }
    return false;
}

bool Custom::onDamaged() {
    return scarfyDamage();
}

bool Custom::onHitPointIsZero() {
    return scarfyDamage();
}

bool Custom::onVacuumResist() {
    if (obj().hitPoint().isDead()) {
        return false;
    }
    if (!mIsFaceChanged) {
        obj().soundSE().start(0x2c6);
        obj().stateChanger().setNextState<StateFaceChange, Enemy*>(&obj());
        mIsFaceChanged = true;
    }
    return true;
}

void Custom::onAngerFlag() {
    mIsAnger = true;
    mIsFaceChanged = true;
}

bool Custom::isAngerFlag() const {
    return mIsAnger;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::scarfy
