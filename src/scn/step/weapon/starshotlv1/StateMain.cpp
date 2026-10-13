#include "scn/step/weapon/starshotlv1/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/starshotlv1/Custom.h"
#include "scn/step/weapon/starshotlv1/Param.h"

namespace {

const scn::step::ocoll::AttackType ATTACK_TYPE_TABLE[] = {
    static_cast<scn::step::ocoll::AttackType>(0x154),
    static_cast<scn::step::ocoll::AttackType>(0x160),
    static_cast<scn::step::ocoll::AttackType>(0x16D),
    static_cast<scn::step::ocoll::AttackType>(0x170),
};

const scn::step::ocoll::AttackType ATTACK_SUB_TYPE_TABLE[] = {
    static_cast<scn::step::ocoll::AttackType>(0x16C),
    static_cast<scn::step::ocoll::AttackType>(0x16C),
    static_cast<scn::step::ocoll::AttackType>(0x173),
    static_cast<scn::step::ocoll::AttackType>(0x173),
};

}

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv1 {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mRot(0.0f), _C(), mScale(0.001f) {
    const Param& param = obj().param().starShotLv1();
    obj().objColl().setAttackType(ATTACK_TYPE_TABLE[obj().variation()]);
    obj().objColl().setAttackTypeSub(ATTACK_SUB_TYPE_TABLE[obj().variation()]);
    obj().objColl().addAttack(0, param.mAttackRadius);
    obj().objColl().addAttackSub(
        0, param.mAttackRadius, hel::math::Vector2(0.0f, -param.mAttackSubOffset),
        hel::math::Vector2(0.0f, param.mAttackSubOffset));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4B3), 0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4B5), 2);
    obj().model().setViewOffset(hel::math::Vector3(0.0f, 0.0f, 0.55f));
}

StateMain::~StateMain() {
    obj().objColl().clearAttack();
}

void StateMain::procAnim() {
    Custom* custom = hel::common::DynamicCast<Custom*, ICustom>(obj().custom());
    if (custom->isHeroDisappeared()) {
        deadWithEffect();
        return;
    }
    const Param& param = obj().param().starShotLv1();
    mRot += param.mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3::BASIS_X, mRot);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(param.mWaterMoveRate);
    } else {
        obj().move().resetMoveRate();
    }
    u32 frame = obj().param().starShotLv1().mScaleFrame;
    if (frame != 0) {
        mScale = hel::math::Math::LimitMax(mScale + 1.0f / frame, 1.0f);
    }
    obj().model().setScale(hel::math::Vector3::ALL_ONE * mScale);
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    const Param& param = obj().param().starShotLv1();
    if (obj().objColl().isAttackCollide()) {
        u32 resistLv = obj().objColl().attack().getCollidedHitResistLv();
        hel::math::Vector3 velocity = obj().move().velocity();
        hel::math::Vector2 hitPos = obj().objColl().attack().getCollidedHitPos();
        f32 diff = hitPos.y - obj().location().pos().y;
        if (resistLv == 6) {
            velocity.x *= param.mResistSpeedRateH;
            velocity.y = param.mResistSpeedV;
            obj().move().setVelocity(velocity);
        } else if (resistLv >= 4) {
            deadWithEffect();
            return;
        } else if (!obj().objColl().isAttackCollideMain()) {
            int sign = diff < 0.0f ? -1 : 1;
            obj().move().setSpeedV(param.mReflectSpeedV * sign);
            obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x16C));
        } else {
            deadWithEffect();
            return;
        }
    }
    if (obj().objColl().attack().isCollideGimmick()) {
        deadWithEffect();
        return;
    }
    if (obj().mapColl().isHit()) {
        deadWithEffect();
    }
}

void StateMain::deadWithEffect() {
    hel::math::Vector3 pos = obj().location().pos();
    obj().comp().permEffect().normal().requestPD(static_cast<effect::Kind>(0x4B1), pos, obj().target().getDirection3());
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x78), pos);
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x4B0), pos);
    obj().comp().permSoundSE().start(0x121);
    obj().dead();
}

}}}}  // namespace scn::step::weapon::starshotlv1
