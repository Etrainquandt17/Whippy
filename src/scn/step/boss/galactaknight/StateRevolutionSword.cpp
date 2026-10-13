#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/galactaknight/StateRevolutionSword.h"

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
#include "scn/step/weapon/galactarevolutionsword/Custom.h"
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
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactarevolutionsword::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}
}

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateRevolutionSword::StateRevolutionSword(Boss* boss) : StateBase(boss), mWeapon(), mIsRequested(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x20);
    obj().guard().setType(static_cast<GuardType>(1));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateRevolutionSword::~StateRevolutionSword() {
    Utility::ControlHateOnAction(obj());
}

void StateRevolutionSword::procAnim() {
    if (obj().scriptTrigger().get(2)) {
        reqRevolutionSword();
    }
    if (mIsRequested && mWeapon.isNull()) {
        obj().brainCtrl().toValid();
    }
}

void StateRevolutionSword::procMove() {}

void StateRevolutionSword::procFixPos() {}

void StateRevolutionSword::reqRevolutionSword() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mIsRequested = true;
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos.x += -0.1f;
    pos.y += 2.8f;
    weapon::Desc desc(static_cast<weapon::Kind>(0x86), 0, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                      obj().objColl().owner());
    desc._24 = Utility::GetHatedHeroPos(obj()).getXY();
    util::ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        mWeapon = weapon;
        weapon::galactarevolutionsword::Custom& weaponCustom =
            hel::common::DynamicCastToRef<weapon::galactarevolutionsword::Custom, weapon::ICustom>(weapon->custom());
        weaponCustom.setFloorPosY(custom.landCtrl().getFloorY());
    }
}

}
}
}
}
