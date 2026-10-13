#include "scn/step/boss/watergalboros/StateCaptureAttack.h"

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
#include "scn/step/boss/watergalboros/StateCapture.h"
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

StateCaptureAttack::StateCaptureAttack(Boss* boss) : StateBase(boss), mCount(0), mIsCapture(false), mIsSearch(false) {
    obj().model().reqScript(0x11);
    Utility::ControlHateOnAction(obj());
}

StateCaptureAttack::~StateCaptureAttack() {
    obj().objColl().clearSearchHit();
}

void StateCaptureAttack::procAnim() {
    const Param& param = obj().param().watergalboros();
    if (mCount < param.mCaptureAttackFrame) {
        mCount++;
    } else {
        if (mIsCapture) {
            obj().stateChanger().setNextState<StateCapture, Boss*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
        }
        return;
    }
    if (mIsSearch) {
        f32 speed = param.mCaptureAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
        mIsSearch = false;
    }
    if (obj().scriptTrigger().get(0)) {
        hel::math::Vector2 offset;
        offset.x = param.mCaptureSearchOffset.x * obj().target().getSign();
        offset.y = param.mCaptureSearchOffset.y;
        hel::math::Vector2 offset2;
        offset2.x = param.mCaptureSearchOffset2.x * obj().target().getSign();
        offset2.y = param.mCaptureSearchOffset2.y;
        obj().objColl().addSearchHit(0, param.mCaptureSearchRadius, offset, offset2);
        mIsSearch = true;
    }
    if (obj().scriptTrigger().get(1)) {
        obj().objColl().clearSearchHit();
    }
}

void StateCaptureAttack::procMove() {
    const Param& param = obj().param().watergalboros();
    obj().move().groundDecel(param._24);
}

void StateCaptureAttack::procObjCollReact() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.captureCtrl().checkCapture()) {
        mIsCapture = true;
    }
}

}}}}  // namespace scn::step::boss::watergalboros
