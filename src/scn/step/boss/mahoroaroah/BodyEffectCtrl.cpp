#include "scn/step/boss/mahoroaroah/BodyEffectCtrl.h"

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
namespace mahoroaroah {

namespace {

const u32 T_TARGET_NODES[] = { 7, 1, 2, 3, 4, 5, 6 };

}

BodyEffectCtrl::BodyEffectCtrl(Boss& boss) : mBoss(boss), mIsVisible(false) {}

BodyEffectCtrl::~BodyEffectCtrl() {}

void BodyEffectCtrl::setVisible(bool isWarp) {
    if (!mIsVisible) {
        mIsVisible = true;
        if (isWarp) {
            mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BE), 10);
        } else {
            for (u32 i = 0; i < 7; i++) {
                mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BB), T_TARGET_NODES[i]);
                mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3BC), T_TARGET_NODES[i]);
                mBoss.effect().normal().requestN(static_cast<effect::Kind>(0x3BD), T_TARGET_NODES[i]);
            }
        }
    }
}

void BodyEffectCtrl::setInvisible() {
    if (mIsVisible) {
        mIsVisible = false;
        mBoss.effect().back().release();
        mBoss.effect().normal().release();
    }
}

void BodyEffectCtrl::reqAfterImage() {
    mBoss.effect().back().requestN(static_cast<effect::Kind>(0x3AF), 10);
}

void BodyEffectCtrl::releaseAfterImage() {
    mBoss.effect().back().release();
}

}}}}  // namespace scn::step::boss::mahoroaroah
