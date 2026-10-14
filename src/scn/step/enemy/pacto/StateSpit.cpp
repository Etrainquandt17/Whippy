#include "scn/step/enemy/pacto/StateSpit.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/pacto/ParamData.h"
#include "scn/step/enemy/pacto/StateBack.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateSpit::StateSpit(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsAnimEnd(false) {
    obj().model().reqScript(10);
}

void StateSpit::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (++mFrame == 8) {
        custom.setDamageCaptureHero(obj().param().pacto().mEatDamage, true);
        if (custom.chkDeadHero()) {
            custom.releaseCaptureHero();
            return;
        }
        custom.vomitCaptureHero();
        obj().soundSE().start(0x50f);
    }
    if (!mIsAnimEnd && obj().model().isAllEnd()) {
        mIsAnimEnd = true;
        obj().model().reqScript(0);
    }
    if (mFrame == obj().param().pacto().mSpitEndFrame) {
        obj().stateChanger().setNextState<StateBack, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::pacto
