#include "scn/step/boss/lowper/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateAppear.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateHide.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFirst::StateFirst(Boss* boss) : StateBase(boss) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().setVisibility(false);
    obj().location().setPos(obj().location().pos() + Vector3::BASIS_Y * 2.5f);
}

StateFirst::~StateFirst() {}

void StateFirst::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.itemCtrl().init();
    if (!custom.itemCtrl().isItemExist()) {
        custom.gearCtrl().setup(static_cast<map::BinItemKind>(0xE), 0);
    }
    if (Utility::IsArena(obj())) {
        obj().stateChanger().setNextState<common::StateAppear, Boss*>(objPtr());
    } else {
        obj().stateChanger().setNextState<StateHide, Boss*>(objPtr());
    }
}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
