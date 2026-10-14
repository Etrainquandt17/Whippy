#include "scn/step/boss/metalgeneral/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

// TODO: a stand-in, as in fattybuffer/StateFirst.cpp: the original reads the two members into temporaries ranked in
// text order, as it does for const value parameters of an inline function. It is a template only so that each of
// the two users expands an instance of its own; one inline function used twice is called.
template <int N>
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(5);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    Rect rect(param._88, param._8C, param._90, param._94);
    t_Trans<0>(rect, obj().basePos().x, obj().basePos().y);
    obj().comp().cameraController().setLock(rect);
    obj().comp().cameraController().resetIntpRate();
    obj().comp().cameraController().setCameraHeightMin(param._AC);
    obj().comp().cameraController().setCameraHeightMax(param._AC);
}

StateFirst::~StateFirst() {}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    const Param& param = obj().param().metalgeneral();
    if (Utility::CanStartAppearance(obj(), -param._A8)) {
        Rect rect(param._98, param._9C, param._A0, param._A4);
        t_Trans<1>(rect, obj().basePos().x, obj().basePos().y);
        obj().comp().cameraController().setLock(rect);
        obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
