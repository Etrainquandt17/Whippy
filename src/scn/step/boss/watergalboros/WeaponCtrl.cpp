#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/watergalboros/WeaponCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
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
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
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
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

WeaponCtrl::WeaponCtrl(Boss& boss) : mBoss(boss) {}

void WeaponCtrl::addReqData(const ReqData& data) {
    mReqBuff.add(data);
}

void WeaponCtrl::clearReqBuff() {
    mReqBuff.clear();
}

WeaponCtrl::ReqData WeaponCtrl::popReqData() {
    ReqData data = mReqBuff[0];
    mReqBuff.removeAtIndex(0);
    return data;
}

bool WeaponCtrl::isReqBuffEmpty() {
    return mReqBuff.count() == 0;
}

void WeaponCtrl::request() {
    const Param& param = mBoss.param().watergalboros();
    while (!isReqBuffEmpty()) {
        ReqData data = popReqData();
        hel::math::Vector2 pos = mBoss.location().pos().getXY();
        hel::math::Vector2 speed(data._4);
        speed.x *= mBoss.target().getSign();
        switch (data._0) {
        case 0:
            pos.x += param._60.x * mBoss.target().getSign();
            pos.y += param._60.y;
            requestBase(static_cast<weapon::Kind>(0x33), pos, speed, 0);
            break;
        case 1:
            pos.x += param._68.x * mBoss.target().getSign();
            pos.y += param._68.y;
            requestBase(static_cast<weapon::Kind>(0x2D), pos, speed, 2);
            break;
        }
    }
}

void WeaponCtrl::requestBase(weapon::Kind kind, hel::math::Vector2 pos, hel::math::Vector2 speed, u32 variation) {
    weapon::Desc desc(kind, variation, static_cast<ostop::Flag>(8), pos, speed, mBoss.objColl().owner());
    mBoss.comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::watergalboros
