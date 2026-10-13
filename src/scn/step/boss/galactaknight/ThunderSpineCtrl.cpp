#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/galactaknight/ThunderSpineCtrl.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactathunderspine/Custom.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactathunderspine::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}
}

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

ThunderSpineCtrl::ThunderSpineCtrl(Boss& boss) : mBoss(boss) {}

void ThunderSpineCtrl::add(const ReqData& data) {
    mBuff.add(data);
}

ThunderSpineCtrl::ReqData ThunderSpineCtrl::pick() {
    ReqData data = mBuff[0];
    mBuff.removeAtIndex(0);
    return data;
}

void ThunderSpineCtrl::clear() {
    mBuff.clear();
}

bool ThunderSpineCtrl::isEmpty() const {
    return mBuff.count() == 0;
}

// TODO: two registers differ in the expanded mWeapons.add(): the original keeps the array element in r30 and the
// handle's list in r29; this gives them swapped.
void ThunderSpineCtrl::request() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    hel::math::Vector2 base(custom.landCtrl().getCenterX(), custom.landCtrl().getFloorY());
    cleanup();
    while (!isEmpty()) {
        if (mWeapons.isFull()) {
            return;
        }
        ReqData data = pick();
        hel::math::Vector2 pos = base;
        pos.x += data._0;
        weapon::Desc desc(static_cast<weapon::Kind>(0x85), 0, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                          mBoss.objColl().owner());
        util::ObjRefHandle<weapon::Weapon> weapon = mBoss.comp().weaponManager().request(desc);
        if (weapon.isAlive()) {
            mWeapons.add(weapon);
        }
    }
    mBoss.soundSE().normal().start(0x3A1);
}

void ThunderSpineCtrl::attack() {
    for (u32 i = 0; i < mWeapons.count(); i++) {
        if (mWeapons[i].isAlive()) {
            weapon::galactathunderspine::Custom& custom =
                hel::common::DynamicCastToRef<weapon::galactathunderspine::Custom, weapon::ICustom>(mWeapons[i]->custom());
            custom.attack();
        }
    }
    mBoss.soundSE().normal().start(0x3A2);
    mWeapons.clear();
}

void ThunderSpineCtrl::cleanup() {
    u32 n = mWeapons.count();
    if (n != 0) {
        for (; n != 0; n--) {
            u32 i = n - 1;
            if (mWeapons[i].isAlive()) {
                mWeapons[i]->dead();
            }
        }
        mWeapons.clear();
    }
}

}
}
}
}
