#include "scn/step/enemy/barracu/StateAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/barracu/Custom.h"
#include "scn/step/enemy/barracu/ParamData.h"
#include "scn/step/enemy/barracu/StateEscape.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

StateAttack::StateAttack(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mDamageFrame(obj().param().barracu().mAttackDamageFrame) {
    obj().model().reqScript(10);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.setDamageCaptureHero(obj().param().barracu().mAttackDamage, false);
    obj().nururi().setCanNururi(false);
    obj().soundSEState().start(0x30a);
}

StateAttack::~StateAttack() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).disableResistCaptureHero();
    obj().nururi().setCanNururi(true);
}

void StateAttack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().barracu();
    if (--mDamageFrame == 0) {
        mDamageFrame = param.mAttackDamageFrame;
        custom.setDamageCaptureHero(param.mAttackDamage, false);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
    }
    mFrame++;
    if (mFrame > param.mAttackEndFrame || custom.chkReleaseHero()) {
        if (custom.chkReleaseHero()) {
            custom.setSuccessCaptureHero();
        }
        obj().soundSEState().stop();
        custom.vomitCaptureHero();
        custom.setDamageCaptureHero(0, true);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
        obj().stateChanger().setNextState<StateEscape, Enemy*>(objPtr());
    }
    if (mFrame == param.mAttackResistFrame) {
        custom.enableResistCaptureHero();
    }
}

}}}}  // namespace scn::step::enemy::barracu
