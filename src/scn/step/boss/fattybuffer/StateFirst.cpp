#include "scn/step/boss/fattybuffer/StateFirst.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
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
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

// TODO: a stand-in. The original reads the two members at once into temporaries ranked in text order, as it does for
// const value parameters of an inline function.
inline void t_Trans(hel::geo::Rect& rect, const f32 x, const f32 y) {
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
        hel::geo::Rect viewRect = obj().comp().mainCamera().getViewRect();
        bool canStart;
        if (Utility::IsStagingFirstAppear(obj())) {
            canStart = Utility::CanStartAppearance(obj(), -param._58);
        } else {
            canStart = Utility::CanStartAppearance(obj(), -param._5C, -param._60);
        }
        if (canStart) {
            hel::geo::Rect rect(param._38, param._3C, param._40, param._44);
            t_Trans(rect, obj().basePos().x, obj().basePos().y);
            obj().comp().cameraController().setLock(rect);
            obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
            return;
        }
    }
}

}
}
}
}
