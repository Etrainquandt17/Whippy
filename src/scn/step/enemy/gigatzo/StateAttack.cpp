#include "scn/step/enemy/gigatzo/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/gigatzo/Custom.h"
#include "scn/step/enemy/gigatzo/ParamData.h"
#include "scn/step/enemy/gigatzo/StateWait.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isBackAttack() || custom.isAir()) {
        obj().footState().setAir();
    } else {
        obj().footState().setGround();
    }
    obj().model().reqScript(7);
    switch (obj().kind()) {
    case 0x39:
        if (custom.isBackAttack()) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54e), 4);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x550), 5);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x550), 6);
        } else {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54d), 4);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54f), 5);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x54f), 6);
        }
        obj().soundSE().start(0x305);
        break;
    case 0x49:
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x58), 1);
        obj().soundSE().start(0x509);
        break;
    }
    obj().brainCtrl().toValid();
}

StateAttack::~StateAttack() {
    obj().effect().normal().release();
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().gigatzo();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    switch (obj().kind()) {
    case 0x22:
        if (mFrame == param.mEffectFrame) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x1a3), 1);
            if (custom.isBackAttack()) {
                obj().effect().normal().changeLayer(static_cast<core::DrawLayerKind>(5));
            }
        } else if (mFrame == param.mShotFrame - 3) {
            shot();
        }
        break;
    case 0x39:
        if (mFrame == param.mEffectFrameSuper) {
            if (custom.isBackAttack()) {
                obj().effect().normal().requestN(static_cast<effect::Kind>(0x552), 2);
            } else {
                obj().effect().normal().requestN(static_cast<effect::Kind>(0x551), 2);
            }
        } else if (mFrame == param.mShotFrame + 3) {
            shot();
        }
        break;
    case 0x49:
        if (mFrame == param.mEffectFrameCannon) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x59), 5);
        } else if (mFrame == param.mShotFrame) {
            shot();
        }
        break;
    }
}

void StateAttack::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().footState().isAir() && !custom.isBackAttack() && !custom.isAir()) {
        obj().move().airDecelFall(obj().param().common().mDecel, obj().param().common().mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateAttack::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.isBackAttack() && !custom.isAir()) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().footState().setGround();
        } else {
            obj().footState().setAir();
            obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        }
    }
}

void StateAttack::shot() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().soundSE().stop();
    switch (obj().kind()) {
    case 0x22:
        if (custom.isBackAttack()) {
            obj().soundSE().start(0x2b3);
        } else {
            obj().soundSE().start(0x2cc);
        }
        break;
    case 0x39:
        obj().soundSE().start(0x508);
        break;
    case 0x49:
        obj().soundSE().start(0x50a);
        break;
    }
    weapon::Desc desc;
    g3d::NodeAccessor node = obj().model().model().nodes().at(2);
    hel::math::Vector2 pos;
    hel::math::Vector2 unused1;
    hel::math::Vector2 unused2;
    switch (obj().kind()) {
    case 0x22:
        desc.mKind = static_cast<weapon::Kind>(0x31);
        pos = node.worldMtx().getT().getXY() - setBulletInitVel() * 0.5f;
        break;
    case 0x39:
        desc.mKind = static_cast<weapon::Kind>(0x3c);
        pos = node.worldMtx().getT().getXY() + setBulletInitVel() * 0.5f;
        break;
    case 0x49:
        desc.mKind = static_cast<weapon::Kind>(0x4c);
        pos = node.worldMtx().getT().getXY();
        break;
    }
    desc.mPos = desc._14 = pos;
    desc.mFlag = static_cast<ostop::Flag>(4);
    desc._1c = setBulletInitVel();
    desc.mOwner = &obj().objColl().owner();
    desc._2c = true;
    if (!custom.isBackAttack()) {
        desc.mVariation = 0;
        obj().comp().weaponManager().request(desc);
    } else {
        desc.mVariation = 1;
        obj().comp().weaponManager().request(desc);
    }
}

hel::math::Vector2 StateAttack::setBulletInitVel() {
    f32 angle = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).aimAngle();
    hel::math::Vector2 vel;
    if (0.0f == angle) {
        vel = hel::math::Vector2(0.0f, 1.0f);
    } else if (-90.0f == angle || 270.0f == angle) {
        vel = hel::math::Vector2(-1.0f, 0.0f);
    } else if (90.0f == angle) {
        vel = hel::math::Vector2(1.0f, 0.0f);
    } else if (-45.0f == angle || 315.0f == angle) {
        vel = hel::math::Vector2(-1.0f, 1.0f);
        vel = vel.getNormalized();
    } else if (45.0f == angle) {
        vel = hel::math::Vector2(1.0f, 1.0f);
        vel = vel.getNormalized();
    }
    return vel;
}

}}}}  // namespace scn::step::enemy::gigatzo
