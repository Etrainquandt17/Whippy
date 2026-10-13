#include "scn/step/boss/watergalboros/StateCapture.h"

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
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/boss/watergalboros/StateVomit.h"
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

StateCapture::StateCapture(Boss* boss) : StateBase(boss), mCount(0), mIsFirst(true) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x12);
    custom.captureCtrl().setInvisibility();
}

StateCapture::~StateCapture() {}

void StateCapture::procAnim() {
    const Param& param = obj().param().watergalboros();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.captureCtrl().setDamage(mIsFirst ? param.mCaptureDamageFirst : param.mCaptureDamage);
        mIsFirst = false;
    }
    if (obj().model().isAllEnd()) {
        if (mCount < param.mCaptureCount) {
            mCount++;
        }
        if (mCount == param.mCaptureCount) {
            obj().stateChanger().setNextState<StateVomit, Boss*, bool>(objPtr(), false);
        } else if (custom.captureCtrl().getResistPower() > param.mCaptureResistPower) {
            obj().stateChanger().setNextState<StateVomit, Boss*, bool>(objPtr(), true);
        } else {
            obj().model().reqScript(0x12);
        }
    }
}

void StateCapture::procMove() {}

void StateCapture::procFixPos() {}

}}}}  // namespace scn::step::boss::watergalboros
