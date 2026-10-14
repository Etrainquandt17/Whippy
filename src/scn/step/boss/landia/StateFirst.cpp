#include "scn/step/boss/landia/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateAppear.h"
#include "scn/step/boss/landia/SwitchModelCtrl.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/hero/BossDemoCtrl.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace landia {

namespace {

// TODO: stand-ins. The original reads the two members at once into temporaries ranked in text order, as it does for
// const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

inline void t_StartBossDemoMode(hero::BossDemoCtrl& ctrl, const f32 left, const f32 right) {
    ctrl.startBossDemoMode(left, right, hero::BossDemoCtrl::DEMO_KIND_0);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(0), mZoomId(0) {
    const Param& param = obj().param().landia();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().invincible().setPermNoFlash();
    custom.waftCtrl().setWaveDefault();
    obj().guard().setType(static_cast<GuardType>(6));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    Vector3 pos = obj().basePos().toVector3() + Vector3(param._138);
    custom.waftCtrl().setRefPos(pos);
    if (obj().level() == 0) {
        {
            f32 width = param._34 * obj().comp().mainCamera().getAspect();
            Rect rect(param._34 + param._30, param._30, -0.5f * width + param._38, 0.5f * width + param._38);
            // TODO: the original keeps this y in f30, not f31; everything else is the same.
            t_Trans(rect, obj().basePos().x, obj().basePos().y);
            obj().comp().cameraController().setLock(rect);
            obj().comp().cameraController().resetIntpRate();
            obj().comp().cameraController().setCameraHeightMin(param._34);
            obj().comp().cameraController().setCameraHeightMax(param._34);
        }
        if (Utility::IsStagingFirstAppear(obj())) {
            Vector2 pos = obj().basePos();
            pos.x += param._138.x;
            pos.y += param._144 + param._148;
            mZoomId = obj().comp().cameraController().setZoom(pos, param._14C, 1.0f);
        }
        if (Utility::IsVariationExtra(obj())) {
            custom.switchModelCtrl().createLandiaDummy();
            obj().model().setVisibility(false);
            obj().shadow().setVisibility(false);
        }
        if (Utility::IsStagingFirstAppear(obj())) {
            t_StartBossDemoMode(obj().comp().heroManager().bossDemoCtrl(), obj().basePos().x, obj().basePos().x);
            obj().comp().infoManager().gameStatus().startAnimOut();
        }
    }
}

StateFirst::~StateFirst() {
    if (Utility::IsStagingFirstAppear(obj())) {
        obj().comp().heroManager().bossDemoCtrl().endBossDemoMode();
    }
}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    const Param& param = obj().param().landia();
    mCount++;
    if (Utility::IsStagingFirstAppear(obj())) {
        if (mCount == 1) {
            obj().comp().screenFade().setFadeIn(param._134);
            obj().comp().screenFade().setStopFrame(param._130);
        }
        if (mCount == param._134 + param._130) {
            obj().stateChanger().setNextState<StateAppear, Boss*, u32>(objPtr(), mZoomId);
        }
    } else {
        if (mCount == param._134 + param._130) {
            obj().stateChanger().setNextState<StateAppear, Boss*, u32>(objPtr(), mZoomId);
        }
    }
}

}}}}  // namespace scn::step::boss::landia
