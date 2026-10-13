#include "scn/step/boss/mahoroaroah/SubAnimCtrl.h"

#include "g3d/ModelAnimAccessor.h"
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

SubAnimCtrl::SubAnimCtrl(Boss& boss) : mBoss(boss), mIsValid(false) {}

void SubAnimCtrl::setup() {
    mBoss.model().anim().subAnimSet(0, 1, 8);
    mBoss.model().anim().subAnimAccessor(0).start(true);
    mBoss.model().anim().subAnimSet(1, 1, 9);
    mBoss.model().anim().subAnimAccessor(1).start(true);
    mIsValid = true;
}

void SubAnimCtrl::update() {
    bool isValid = chkValidAnim();
    if (mIsValid != isValid) {
        mIsValid = isValid;
        mBoss.model().anim().subAnimClear(1);
        if (mIsValid) {
            mBoss.model().anim().subAnimSet(1, 1, 9);
            mBoss.model().anim().subAnimAccessor(1).start(true);
        }
    }
}

bool SubAnimCtrl::chkValidAnim() {
    switch (mBoss.model().anim().currentG3DAnimIndex()) {
    case 8:
    case 9:
        return false;
    default:
        return true;
    }
}

}
}
}
}
