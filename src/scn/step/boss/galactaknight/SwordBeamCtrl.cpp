#include "scn/step/boss/galactaknight/SwordBeamCtrl.h"

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
#include "scn/step/weapon/galactaswordbeam/Custom.h"
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
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactaswordbeam::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}
}

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

SwordBeamCtrl::SwordBeamCtrl(Boss& boss) : mBoss(boss) {}

void SwordBeamCtrl::add(const ReqData& data) {
    if (!mBuff.isFull()) {
        mBuff.add(data);
        u32 index = mBuff.count() - 1;
        mBuff[index].mIndex = index;
    }
}

void SwordBeamCtrl::clear() {
    mBuff.clear();
}

bool SwordBeamCtrl::isEmpty() const {
    return mBuff.count() == 0;
}

SwordBeamCtrl::ReqData SwordBeamCtrl::pick() {
    ReqData data = mBuff[0];
    mBuff.removeAtIndex(0);
    return data;
}

void SwordBeamCtrl::shuffleIndex() {
    hel::common::MutableArray<ReqData, 12> buff = mBuff;
    for (u32 i = 0; buff.count() != 0; i++) {
        u32 index = app::Random::RandU32(buff.count());
        mBuff[i].mIndex = buff[index].mIndex;
        buff.removeAtIndex(index);
    }
}

// TODO: three registers differ: the original keeps the parameters in r31, the custom in r30 and the variation in r29;
// this gives r30, r29 and r31.
void SwordBeamCtrl::requestOne() {
    const Param& param = mBoss.param().galactaknight();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    if (!isEmpty()) {
        ReqData data = pick();
        hel::math::Vector2 pos = mBoss.location().pos().getXY();
        pos.y += 1.0f;
        hel::math::Vector2 dir = hel::math::Vector2::BASIS_X;
        dir.rotate(0.017453292f * data._0);
        dir.x *= mBoss.target().getSign();
        dir *= 0.5f;
        weapon::Desc desc(static_cast<weapon::Kind>(0x87), data._4 ? 1 : 0, static_cast<ostop::Flag>(8), pos, dir,
                          mBoss.objColl().owner());
        if (data._4) {
            f32 x = param._EC + param._F0 * static_cast<f32>(data.mIndex) / 11.0f;
            desc._24.x = x * mBoss.target().getSign() + custom.landCtrl().getCenterX();
            desc._24.y = 1.0f + (param._40 + custom.landCtrl().getFloorY());
        }
        util::ObjRefHandle<weapon::Weapon> weapon = mBoss.comp().weaponManager().request(desc);
        if (weapon.operator->() != 0) {
            weapon::galactaswordbeam::Custom& weaponCustom =
                hel::common::DynamicCastToRef<weapon::galactaswordbeam::Custom, weapon::ICustom>(weapon->custom());
            weaponCustom.setIsReqStarEffect(data._5);
            if (data._4) {
                hel::math::Vector3 weaponPos = pos.toVector3();
                weaponPos.z = mBoss.location().pos().z;
                weapon->location().setPos(weaponPos);
            }
        }
        mBoss.soundSE().normal().start(0x397);
    }
}

}
}
}
}
