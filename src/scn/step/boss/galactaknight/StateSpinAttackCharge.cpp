#include "scn/step/boss/galactaknight/StateSpinAttackCharge.h"

#include "app/Random.h"
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
#include "scn/step/boss/galactaknight/StateSpinAttack.h"
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
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateSpinAttackCharge::StateSpinAttackCharge(Boss* boss, u32 frame, f32 distance, u32 count)
    : StateBase(boss), mFrame(frame), mIsStart(false), mDistance(distance), mCount(count) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().guard().setType(static_cast<GuardType>(1));
    obj().model().reqScript(0x19);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateSpinAttackCharge::~StateSpinAttackCharge() {
    obj().soundSE().loop().stop();
}

void StateSpinAttackCharge::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (obj().scriptTrigger().get(0)) {
        mIsStart = true;
        obj().model().rotCtrl().setRotHIntpRate(param._BC);
    }
    if (mIsStart) {
        if (mFrame > param._B8) {
            Utility::TurnHatedHero(obj());
        }
        if (mFrame != 0) {
            mFrame--;
        } else {
            obj().stateChanger().setNextState<StateSpinAttack, Boss*, f32, u32>(objPtr(), mDistance, mCount);
        }
    }
}

void StateSpinAttackCharge::procMove() {}

void StateSpinAttackCharge::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
