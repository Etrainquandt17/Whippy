#include "scn/step/boss/hrd3pilot/TailCtrl.h"

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
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

namespace {

const f32 T_STORAGE_SCALE = 0.3f;

}

TailCtrl::TailCtrl(Boss& boss) : mBoss(boss), mIsStored(false), mCount(0) {}

void TailCtrl::update() {
    if (mIsStored) {
        if (mCount < 30) {
            mCount++;
        } else {
            return;
        }
    } else {
        if (mCount != 0) {
            mCount--;
        } else {
            return;
        }
    }
    if (mCount == 30 && mIsStored) {
        mBoss.effect().normal().release();
    }
    f32 t = (f32)mCount / 30.0f;
    f32 scale = hel::math::Math::LinearInterpolation(1.0f, T_STORAGE_SCALE, t);
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateScale(hel::math::Vector3(1.0f, scale, 1.0f));
    mBoss.model().model().nodes().at(6).localMtx().setRTMtx(mtx);
}

void TailCtrl::storage() {
    mIsStored = true;
}

void TailCtrl::extract() {
    if (mIsStored) {
        mIsStored = false;
        mBoss.effect().normal().requestN(static_cast<effect::Kind>(0x459), 5);
    }
}

}
}
}
}
