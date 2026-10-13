#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/roahboomerang/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahboomerang/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahboomerang {

StateMain::StateMain(Weapon* weapon)
    : StateBase(weapon)
    , mFrame(0)
    , mMoveFrame(0)
    , mEndFrame(0)
    , mStartPos()
    , mRange()
    , mRangeBack()
    , mHitInterval(0) {
    const Param& param = obj().param().roahBoomerang();
    obj().mapColl().setValid(false);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1F6));
    obj().objColl().addAttack(0, param._0);
    obj().objColl().addHit(0, param._4);
    obj().move().resetVelocity();
    obj().model().rotCtrl().initRotH(-90.0f);
    obj().model().reqScript(0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4CF), 0);
    mStartPos = obj().location().pos();
    if (Utility::IsExtra(obj())) {
        mMoveFrame = param._18;
    } else {
        mMoveFrame = param._14;
    }
    switch (obj().variation()) {
    case 0:
        if (Utility::IsExtra(obj())) {
            mRange = hel::math::Vector2(param._28);
        } else {
            mRange = hel::math::Vector2(param._20);
        }
        mRangeBack = hel::math::Vector2(param._30);
        obj().model().model().nodes().at(2).setVisibility(false);
        break;
    case 1:
        if (Utility::IsExtra(obj())) {
            mRange = hel::math::Vector2(param._40);
        } else {
            mRange = hel::math::Vector2(param._38);
        }
        mRangeBack = hel::math::Vector2(param._48);
        obj().model().model().nodes().at(1).setVisibility(false);
        break;
    }
}

void StateMain::procAnim() {
    const Param& param = obj().param().roahBoomerang();
    if (mFrame < mMoveFrame) {
        mFrame++;
    } else if (mEndFrame < param._1C) {
        mEndFrame++;
        if (mEndFrame == 1) {
            u32 num = obj().comp().bossManager().getBossCount();
            for (u32 i = 0; i < num; i++) {
                util::ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
                if (boss.isAlive() && boss->kind() == 0xE) {
                    hel::common::DynamicCastToRef<boss::roah::Custom, boss::ICustom>(boss->custom())
                        .weaponCtrl()
                        .caughtSignal();
                }
            }
            obj().model().setVisibility(false);
        }
    } else {
        obj().dead();
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().roahBoomerang();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mMoveFrame);
    hel::math::Vector3 pos = mStartPos;
    if (Utility::IsExtra(obj())) {
        t += param._C * hel::math::Math::SinDegF(1440.0f * t);
        pos.x -= mRange.x
                 * (1.0f
                    - (1.0f - hel::math::Math::SinDegF(180.0f * t)) * (1.0f - hel::math::Math::SinDegF(180.0f * t)));
        pos.x += mRangeBack.x
                 * (hel::math::Math::SinDegF(180.0f * t) * hel::math::Math::SinDegF(180.0f * t)
                    * hel::math::Math::SinDegF(180.0f * t));
        pos.y -= mRange.y * hel::math::Math::SinDegF(720.0f * t);
        f32 sign = obj().variation() == 0 ? -1.0f : 1.0f;
        pos.z += sign * param._10 * hel::math::Math::SinDegF(360.0f * t);
    } else {
        t += param._8 * hel::math::Math::SinDegF(720.0f * t);
        pos.x -= mRange.x * hel::math::Math::SinDegF(180.0f * t);
        pos.y -= mRange.y * hel::math::Math::SinDegF(360.0f * t);
        f32 sign = obj().variation() == 0 ? -1.0f : 1.0f;
        pos.z += sign * param._10 * hel::math::Math::SinDegF(360.0f * t);
    }
    obj().location().setPos(pos);
}

void StateMain::procFixPos() {
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

}}}}  // namespace scn::step::weapon::roahboomerang
