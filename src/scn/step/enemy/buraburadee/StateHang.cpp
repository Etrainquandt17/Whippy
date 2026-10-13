#include "scn/step/enemy/buraburadee/StateHang.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/buraburadee/Custom.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

StateHang::StateHang(Enemy* enemy) : StateBase(enemy) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    if (obj().kind() == 0x42) {
        u32 script = obj().target().isRightDir() ? 0x17 : 0x19;
        obj().model().reqScript(script);
    } else {
        u32 script = obj().target().isRightDir() ? 0x10 : 0x12;
        obj().model().reqScript(script);
    }
    if (!obj().target().isRightDir()) {
        obj().model().anim().setFrame(15.0f);
    }
    custom.ropeFixAnim();
    custom.ropeFixMove();
}

void StateHang::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.ropeFixAnim();
    custom.deeAnimDecide();
    if (custom.isStateChange()) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
        custom.offStateChange();
    }
}

void StateHang::procMove() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).ropeFixMove();
}

void StateHang::procFixPos() {}

}}}}  // namespace scn::step::enemy::buraburadee
