#include "scn/step/boss/landia/StateSeparation.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateSeparation::StateSeparation(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(32);
    custom.waftCtrl().setWaveWidthZero();
    obj().guard().setType(GUARD_TYPE_1);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
}

StateSeparation::~StateSeparation() {}

void StateSeparation::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        obj().model().setVisibility(false);
        obj().shadow().setVisibility(false);
        obj().brainCtrl().toValid();
        custom.singleCtrl().generate();
        obj().guard().setType(GUARD_TYPE_1);
        custom.collisionCtrl().setState(CollisionCtrl::STATE_5);
        obj().comp().screenFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x64 });
        obj().comp().screenFade().setFadeIn(40);
    }
}

void StateSeparation::procMove() {
    const Param& param = obj().param().landia();
    obj().move().decel(param.mDecel);
}

void StateSeparation::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
