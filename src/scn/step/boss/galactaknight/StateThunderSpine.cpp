#include "scn/step/boss/galactaknight/StateThunderSpine.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateThunderSpine::StateThunderSpine(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1F);
    obj().guard().setType(static_cast<GuardType>(1));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateThunderSpine::~StateThunderSpine() {}

void StateThunderSpine::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(2)) {
        custom.thunderSpineCtrl().request();
    }
    if (obj().scriptTrigger().get(3)) {
        custom.thunderSpineCtrl().attack();
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateThunderSpine::procMove() {}

void StateThunderSpine::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
