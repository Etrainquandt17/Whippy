#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/roahoar/StatePursuit.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahoar/Param.h"
#include "snd/SERequestor.h"

using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

StatePursuit::StatePursuit(Weapon* weapon)
    : StateBase(weapon)
    , mFrame(0)
    , mLeadPos()
    , mSidePos()
    , mPrevPos()
    , mLeadDir()
    , mSideDir()
    , mLeadSpeed(0.0f)
    , mSideSpeed(0.0f)
    , mRotV(0.0f)
    , mSpin(0.0f) {
    const Param& param = obj().param().roahOar();
    obj().move().resetVelocity();
    obj().model().reqScript(1);
    mSideDir = Vector3::BASIS_Y;
    f32 angle = 0.017453292f * param._30;
    angle *= obj().target().getSign();
    mSideDir.rotate(Vector3::AXIS_Z, angle);
    if (!mSideDir.isZeroLoose(0.00001f)) {
        mSideDir.normalize();
    }
    Vector3 target = Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
        if (boss.isAlive() && boss->kind() == 0xE) {
            target = boss::Utility::GetHatedHeroPos(*boss.operator->());
        }
    }
    Vector2 offset(param._34);
    mLeadDir = target + offset.toVector3() - obj().location().pos();
    f32 length = mLeadDir.length();
    mLeadSpeed = length / static_cast<f32>(param._28);
    mSideSpeed = (param._2C - length) / static_cast<f32>(param._28);
    if (!mLeadDir.isZeroLoose(0.00001f)) {
        mLeadDir.normalize();
    }
    mLeadPos = obj().location().pos();
    mSidePos = obj().location().pos();
    mPrevPos = obj().location().pos();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4CB), 0);
    obj().soundSE().start(0x457);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1F8));
    if (Utility::IsExtra(obj())) {
        obj().objColl().addAttack(1, param._4);
    } else {
        obj().objColl().addAttack(1, param._0);
    }
}

void StatePursuit::procAnim() {
    const Param& param = obj().param().roahOar();
    if (mFrame < param._24) {
        mFrame++;
    } else {
        obj().dead();
        return;
    }
    if (Utility::IsExtra(obj())) {
        mSpin += param._40;
        if (mSpin > 360.0f) {
            mSpin -= 360.0f;
        }
        obj().model().model().nodes().at(0).localMtx().setRTMtx(
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mSpin))
        );
    }
}

void StatePursuit::procMove() {
    const Param& param = obj().param().roahOar();
    if (mFrame < param._28) {
        mLeadPos += mLeadDir * mLeadSpeed;
        mSidePos += mSideDir * mSideSpeed;
        f32 t = static_cast<f32>(mFrame + 1) / static_cast<f32>(param._28);
        Vector3 pos = Math::LinearInterpolation(mSidePos, mLeadPos, t);
        pos.z = mPrevPos.z * (1.0f - t);
        Vector3 velocity = pos - mPrevPos;
        obj().move().setVelocity(velocity);
        mPrevPos = pos;
    }
    obj().move().decel(gobj::MoveParamDecel::Create(0.0f));
    Vector3 diff = obj().location().pos() - obj().location().prevPos();
    if (diff.length() > 0.0f && Math::Abs(diff.x) > 0.0f) {
        f32 limit = Math::Abs(Math::TanF(Math::DegToRad(mRotV)));
        if (Math::Abs(diff.y / diff.x) > limit) {
            mRotV += diff.y > 0.0f ? -param._3C : param._3C;
            obj().model().rotCtrl().initRotV(mRotV);
        }
    }
}

void StatePursuit::procFixPos() {}

}}}}  // namespace scn::step::weapon::roahoar
