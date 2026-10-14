#include "scn/step/boss/galactaknight/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

namespace {

// TODO: a stand-in, as in fattybuffer/StateFirst.cpp: the original reads the two members into temporaries ranked in
// text order, as it does for const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(boss->param().galactaknight()._F4) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    Vector3 pos = obj().basePos().toVector3();
    pos.y += param._F8;
    obj().location().setPos(pos);
    obj().model().reqScript(0x28);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    Rect rect(param._40, param._44, param._48, param._4C);
    t_Trans(rect, obj().basePos().x, obj().basePos().y);
    obj().comp().cameraController().unsetLock();
    obj().comp().cameraController().setLock(rect);
    obj().comp().cameraController().resetIntpRate();
}

StateFirst::~StateFirst() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
}

void StateFirst::procAnim() {
    if (mCount != 0) {
        mCount--;
    }
}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    if (mCount == 0) {
        obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::galactaknight
