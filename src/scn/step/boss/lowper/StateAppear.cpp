#include "scn/step/boss/lowper/StateAppear.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateAppear::StateAppear(Boss* boss) : StateBase(boss), mZoomHandle(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().setVisibility(true);
    if (custom.itemCtrl().isItemExist()) {
        obj().location().setPos(custom.itemCtrl().getItemPos());
    }
    if (obj().comp().bossManager().getBossCount() < 2) {
        mZoomHandle = obj().comp().cameraController().setZoom(obj().location().pos().getXY(), 8.25f);
    }
    Utility::TurnMainHero(obj());
    obj().model().reqScript(1);
}

StateAppear::~StateAppear() {
    obj().comp().cameraController().unsetZoom(mZoomHandle);
}

void StateAppear::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::TurnMainHero(obj());
        obj().brainCtrl().toValid();
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
