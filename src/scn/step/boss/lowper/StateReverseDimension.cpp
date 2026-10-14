#include "scn/step/boss/lowper/StateReverseDimension.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/sfx/Manager.h"
#include "scn/step/sfx/ReverseWorld.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateReverseDimension::StateReverseDimension(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x29);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateReverseDimension::~StateReverseDimension() {}

void StateReverseDimension::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        obj().comp().sfxManager().reverseWorld().startAnim(90);
        obj().soundSE().normal().start(0x563);
        obj().comp().screenFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x80 });
        obj().comp().screenFade().setFadeIn(30);
    }
}

void StateReverseDimension::procMove() {}

void StateReverseDimension::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
