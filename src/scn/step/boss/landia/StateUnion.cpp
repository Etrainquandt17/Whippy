#include "scn/step/boss/landia/StateUnion.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateUnion::StateUnion(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(33);
    custom.waftCtrl().setWaveWidthZero();
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
    custom.singleCtrl().dead();
    obj().guard().setType(GUARD_TYPE_1);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().comp().screenFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x64 });
    obj().comp().screenFade().setFadeIn(40);
}

StateUnion::~StateUnion() {
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    if (obj().location().pos().x < heroPos.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

void StateUnion::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateUnion::procMove() {
    const Param& param = obj().param().landia();
    obj().move().decel(param.mDecel);
}

void StateUnion::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
