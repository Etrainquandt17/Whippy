#include "scn/step/enemy/pacto/StateEat.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/pacto/ParamData.h"
#include "scn/step/enemy/pacto/StateSpit.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateEat::StateEat(Enemy* enemy) : StateBase(enemy), mFrame(0), mDamageWait(0) {
    const ParamData& param = obj().param().pacto();
    mDamageWait = param.mEatDamageInterval;
    if (obj().kind() == 0x4c) {
        mDamageWait = param.mEatDamageIntervalSuper;
    }
    obj().model().reqScript(9);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enableResistCaptureHero();
    custom.setDamageCaptureHero(obj().param().pacto().mEatFirstDamage, false);
    obj().soundSEState().start(0x2f2);
}

StateEat::~StateEat() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).disableResistCaptureHero();
}

void StateEat::procAnim() {
    const ParamData& param = obj().param().pacto();
    mFrame++;
    mDamageWait--;
    if (mDamageWait == 0) {
        mDamageWait = param.mEatDamageInterval;
        if (obj().kind() == 0x4c) {
            mDamageWait = param.mEatDamageIntervalSuper;
        }
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        if (custom.chkReleaseHero()) {
            custom.setSuccessCaptureHero();
            obj().stateChanger().setNextState<StateSpit, Enemy*>(objPtr());
        } else if (mFrame > param.mEatFrame) {
            obj().stateChanger().setNextState<StateSpit, Enemy*>(objPtr());
        } else {
            custom.setDamageCaptureHero(param.mEatDamage, false);
        }
    }
}

}}}}  // namespace scn::step::enemy::pacto
