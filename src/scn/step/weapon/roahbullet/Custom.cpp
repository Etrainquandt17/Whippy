#include "scn/step/weapon/roahbullet/Custom.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/StateAppear.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCast;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mWaitNum(0), mGenerateNum(0), mHitInterval(0) {}

bool Custom::onInit() {
    Custom* custom = DynamicCast<Custom*, ICustom>(obj().custom());
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    custom->setSubAnim();
    obj().setVisibility(false);
    if (obj().variation() == 2) {
        obj().soundSE().start(0x45B);
    }
    obj().stateChanger().setNextState<StateAppear, Weapon*>(&obj());
    return true;
}

void Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x7A), obj().location().pos());
}

void Custom::procFixPos() {
    if (mHitInterval != 0) {
        mHitInterval--;
    } else if (obj().objColl().hit().isCollide()) {
        switch (obj().objColl().hit().getCollidedAttackType()) {
        case 0x10B:
        case 0x10C:
        case 0x10D:
        case 0x10E:
        case 0x10F:
        case 0x110:
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0xDD), obj().location().pos());
            obj().comp().permSoundSE().start(0x299);
            mHitInterval = 10;
            break;
        }
    }
}

void Custom::setSubAnim() {
    u32 anim = 4;
    switch (obj().variation()) {
    case 0:
        anim = 1;
        break;
    case 1:
        anim = 2;
        break;
    case 2:
        anim = 3;
        break;
    }
    obj().model().anim().subAnimSet(0, anim, 0);
    obj().model().anim().subAnimAccessor(0).start(true);
}

void Custom::setWaitNum(u32 num) {
    mWaitNum = num;
}

u32 Custom::waitNum() {
    return mWaitNum;
}

void Custom::setGenerateNum(u32 num) {
    mGenerateNum = num;
}

u32 Custom::generateNum() {
    return mGenerateNum;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::roahbullet
