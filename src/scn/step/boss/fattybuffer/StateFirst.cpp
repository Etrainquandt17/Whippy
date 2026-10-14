#include "scn/step/boss/fattybuffer/StateFirst.h"

#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"

using hel::geo::Rect;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

// TODO: a stand-in. The original reads the two members at once into temporaries ranked in text order, as it does for
// const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(0) {
    obj().invincible().setPermNoFlash();
    obj().model().reqScript(0x33);
    obj().guard().setType(static_cast<GuardType>(6));
    obj().shadow().setVisibility(false);
}

StateFirst::~StateFirst() {}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    const Param& param = obj().param().fattybuffer();
    if (mCount < 60) {
        mCount++;
    } else {
        Rect viewRect = obj().comp().mainCamera().getViewRect();
        bool canStart;
        if (Utility::IsStagingFirstAppear(obj())) {
            canStart = Utility::CanStartAppearance(obj(), -param._58);
        } else {
            canStart = Utility::CanStartAppearance(obj(), -param._5C, -param._60);
        }
        if (canStart) {
            Rect rect(param.mAppearCameraLockTop, param.mAppearCameraLockBottom,
                      param.mAppearCameraLockLeft, param.mAppearCameraLockRight);
            t_Trans(rect, obj().basePos().x, obj().basePos().y);
            obj().comp().cameraController().setLock(rect);
            obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
            return;
        }
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
