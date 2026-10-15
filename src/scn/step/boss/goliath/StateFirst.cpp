#include "scn/step/boss/goliath/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateAppear.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
}

StateFirst::~StateFirst() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
}

void StateFirst::procAnim() {}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    if (mFrame < 60) {
        mFrame++;
        return;
    }
    Rect rect = obj().comp().mainCamera().getViewRect();
    bool canStart;
    if (Utility::IsStagingFirstAppear(obj())) {
        canStart = Utility::CanStartAppearance(obj(), -13.0f);
    } else {
        canStart = Utility::CanStartAppearance(obj(), -14.5f, -7.0f);
    }
    if (canStart) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).cameraCtrl().startAppear();
        obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
        return;
    }
}

}}}}  // namespace scn::step::boss::goliath
