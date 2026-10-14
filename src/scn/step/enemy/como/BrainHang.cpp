#include "scn/step/enemy/como/BrainHang.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/StateCutFall.h"
#include "scn/step/enemy/como/StateHang.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace como {

BrainHang::BrainHang(Enemy& enemy) : BrainBase(enemy) {}

bool BrainHang::onStart() {
    obj().stateChanger().setNextState<StateHang, Enemy*>(&obj());
    DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().setLength(0.0f);
    return true;
}

bool BrainHang::onRecover() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().isCut()) {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(&obj());
    } else {
        return onStart();
    }
    return true;
}

}}}}  // namespace scn::step::enemy::como
