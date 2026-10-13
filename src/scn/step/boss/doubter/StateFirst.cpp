#include "scn/step/boss/doubter/StateFirst.h"

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
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateAppear.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

namespace {

// TODO: a stand-in. The original reads the two members at once into temporaries ranked in text order, as it does for
// const value parameters of an inline function.
inline void t_Trans(hel::geo::Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(0), mFrame(60) {
    obj().invincible().setPermNoFlash();
    if (Utility::IsStagingFirstAppear(obj())) {
        obj().footState().setGround();
        obj().model().reqScript(6);
    } else {
        obj().footState().setAir();
        hel::math::Vector3 pos = obj().location().pos();
        pos.y += obj().param().doubter()._44;
        obj().location().setPos(pos);
    }
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_0);
    obj().guard().setType(static_cast<GuardType>(6));
}

StateFirst::~StateFirst() {}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        hel::geo::Rect viewRect = obj().comp().mainCamera().getViewRect();
        bool canStart;
        if (Utility::IsStagingFirstAppear(obj())) {
            canStart = Utility::CanStartAppearance(obj(), -13.0f);
        } else {
            canStart = Utility::CanStartAppearance(obj(), -14.5f, -7.0f);
        }
        if (canStart) {
            hel::geo::Rect rect(7.0f, -2.0f, -12.0f, 4.0f);
            t_Trans(rect, obj().basePos().x, obj().basePos().y);
            obj().comp().cameraController().setLock(rect);
            obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
            return;
        }
    }
}

}}}}  // namespace scn::step::boss::doubter
