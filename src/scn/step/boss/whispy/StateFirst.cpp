#include "scn/step/boss/whispy/StateFirst.h"

#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MoveLimitResponseCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mStep(0), mCount(0), mSpeed(0.0f) {
    const Param& param = obj().param().whispy();
    {
        hel::geo::Rect rect(param.mFirstWorldRect[0], param.mFirstWorldRect[1], param.mFirstWorldRect[2], param.mFirstWorldRect[3]);
        obj().comp().mainCamera().setWorldRect(rect);
        obj().comp().cameraController().setMainTargetOnlyMode();
    }
    obj().comp().heroManager().moveLimitResponseCtrl().setResponseSpaceJumpToMainPlayer();
    obj().invincible().setPermNoFlash();
    u32 script = 0;
    if (Utility::IsStagingFirstAppear(obj())) {
        script = 5;
    }
    obj().model().reqScript(script);
}

StateFirst::~StateFirst() {}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    const Param& param = obj().param().whispy();
    if (mCount < param.mFirstWaitFrame) {
        mCount++;
        return;
    }
    hel::geo::Rect worldRect = obj().comp().mainCamera().getWorldRect();
    hel::geo::Rect viewRect = obj().comp().mainCamera().getViewRect();
    switch (mStep) {
    case 0:
        if (viewRect._4 <= param.mLockRect[1]) {
            hel::geo::Rect rect(param.mLockRect[0], param.mLockRect[1], param.mFirstWorldRect[2], param.mFirstWorldRect[3]);
            obj().comp().mainCamera().setWorldRect(rect);
            mStep++;
        }
        break;
    case 1: {
        worldRect._C += mSpeed;
        f32 max = param.mLockRect[3];
        f32 distance = param.mFirstAppearDistance;
        if (worldRect._C > max) {
            worldRect._C = max;
        }
        if (mSpeed < param.mFirstScrollSpeedMax) {
            mSpeed += param.mFirstScrollAccel;
        }
        obj().comp().mainCamera().setWorldRect(worldRect);
        distance -= obj().basePos().x;
        if (Utility::CanStartAppearance(obj(), distance)) {
            hel::geo::Rect rect(param.mLockRect[0], param.mLockRect[1], param.mLockRect[2], param.mLockRect[3]);
            obj().comp().cameraController().setLock(rect);
            obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
            return;
        }
        break;
    }
    }
}

}
}
}
}
