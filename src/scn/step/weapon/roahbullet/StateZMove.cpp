#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/roahbullet/StateZMove.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"

using hel::common::DynamicCast;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

StateZMove::StateZMove(Weapon* weapon) : StateBase(weapon), mFrame(0), mPassFrame(0) {
    const Param& param = obj().param().roahBullet();
    obj().culling().setValid(false);
    mStartPos = static_cast<const Component&>(obj().comp()).mainCamera().getCenter().toVector3() + param._48;
    Vector3 target = Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
        if (boss.isAlive() && boss->kind() == 0xE) {
            target = boss::Utility::GetHatedHeroPos(*boss.operator->());
        }
    }
    mTargetPos = target;
    mTargetPos.z = param._54;
}

void StateZMove::procAnim() {
    const Param& param = obj().param().roahBullet();
    if (mFrame < param._44) {
        mFrame++;
    } else {
        obj().dead();
        return;
    }
    f32 rate = static_cast<f32>(mFrame % param._58) / static_cast<f32>(param._58);
    obj().model().model().nodes().at(0).localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, 360.0f * -rate))
    );
}

void StateZMove::procMove() {
    const Param& param = obj().param().roahBullet();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param._44);
    Vector3 pos = Vector3::ZERO;
    pos.x = Math::LinearInterpolation(mStartPos.x, mTargetPos.x, Math::SinDegF(90.0f * rate));
    pos.y = Math::LinearInterpolation(mStartPos.y, mTargetPos.y, 1.0f - POW2(1.0f - Math::SinDegF(90.0f * rate)));
    if (mPassFrame != 0) {
        f32 t = static_cast<f32>(mFrame - mPassFrame) / static_cast<f32>(param._44 - mPassFrame);
        pos.y += param._48.y * (1.0f - Math::CosDegF(90.0f * t));
    }
    pos.z = Math::LinearInterpolation(
        mStartPos.z,
        mTargetPos.z,
        (1.0f - Math::CosDegF(90.0f * rate)) * (1.0f - Math::CosDegF(90.0f * rate))
    );
    obj().location().setPos(pos);
}

void StateZMove::procFixPos() {
    const Param& param = obj().param().roahBullet();
    DynamicCast<Custom*, ICustom>(obj().custom())->procFixPos();
    obj().objColl().clearAttack();
    obj().objColl().clearHit();
    if (Math::Abs(obj().location().pos().z) < param._5C) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1FA));
        obj().objColl().addAttack(0, param._0);
        obj().objColl().addHit(0, param._4);
    }
    if (obj().location().pos().z > 0.0f && mPassFrame == 0) {
        mPassFrame = mFrame;
    }
}

}}}}  // namespace scn::step::weapon::roahbullet
