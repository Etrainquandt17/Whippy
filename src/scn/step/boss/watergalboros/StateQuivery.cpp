#include "scn/step/boss/watergalboros/StateQuivery.h"

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
#include "scn/step/boss/watergalboros/ScriptKind.h"
#include "scn/step/boss/watergalboros/StateAttackJoint.h"
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

StateQuivery::StateQuivery(Boss* boss, Config config) : StateBase(boss), mRot(0.0f), mCount(0), mConfig(config), mIsStart(false) {
    mRot = 90.0f;
    obj().footState().setGround();
    obj().model().reqScript(0xC);
}

StateQuivery::~StateQuivery() {}

void StateQuivery::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsStart = true;
    }
    if (mIsStart) {
        if (++mCount % mConfig._4 == 0) {
            reqQuivery();
        }
        mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, 360.0f / (f32)mConfig._0);
        obj().model().rotCtrl().initRotH(mRot);
        if (mCount == mConfig._0) {
            obj().stateChanger().setNextState<StateAttackJoint, Boss*, ScriptKind>(objPtr(), SCRIPT_KIND_13);
        }
    }
}

void StateQuivery::procMove() {
    const Param& param = obj().param().watergalboros();
    obj().move().groundDecel(param._24);
}

void StateQuivery::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateQuivery::reqQuivery() {
    const Param& param = obj().param().watergalboros();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mQuiveryOffset.x * obj().target().getSign(), param.mQuiveryOffset.y);
    hel::math::Vector2 speed(param.mQuiverySpeed.x * app::Random::RandAF(), param.mQuiverySpeed.y);
    weapon::Desc desc(static_cast<weapon::Kind>(0x33), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}
}
}
}
