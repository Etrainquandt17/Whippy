#include "scn/step/enemy/como/StateHang.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/StateCutFall.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateHang::StateHang(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.threadCtrl().setLength(custom.threadCtrl().getMaxLength());
    obj().objColl().clearSearchAttack();
    obj().objColl().addSearchAttack(
        0, 0.1f, Vector2(0.0f, 1.2f * Utility::GetModelScaleBySizeType(obj())),
        Vector2(0.0f, custom.threadCtrl().getLength() + 1.3f * Utility::GetModelScaleBySizeType(obj())));
}

void StateHang::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.threadCtrl().setLength(custom.threadCtrl().getMaxLength());
}

void StateHang::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().objColl().clearSearchAttack();
    obj().objColl().addSearchAttack(
        0, 0.1f, Vector2(0.0f, 1.2f * Utility::GetModelScaleBySizeType(obj())),
        Vector2(0.0f, custom.threadCtrl().getLength() + 1.3f * Utility::GetModelScaleBySizeType(obj())));
}

void StateHang::procObjCollReact() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().checkCut()) {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::como
