#include "scn/step/boss/doubter/StateJugglingAttack.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJugglingAttack::StateJugglingAttack(Boss* boss, JugglingShotKind kind) : StateBase(boss), mIsFirst(true), mKind(kind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    custom.jugglingCtrl().signalAllEnemyPrepare();
    if (custom.jugglingCtrl().isHoldHero()) {
        custom.jugglingCtrl().shotPrepareHero();
    }
    custom.jugglingCtrl().inactivateEnf();
    obj().model().reqScript(29);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(1));
}

StateJugglingAttack::~StateJugglingAttack() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().clearCapture();
}

void StateJugglingAttack::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        if (custom.jugglingCtrl().isHoldHero()) {
            custom.jugglingCtrl().shotHero();
        } else {
            switch (mKind) {
            case JugglingShotKind_Normal:
                if (mIsFirst) {
                    mIsFirst = false;
                    custom.jugglingCtrl().signalEnemyShot();
                } else {
                    custom.jugglingCtrl().signalEnemyShotRand();
                }
                break;
            case JugglingShotKind_Fast:
                custom.jugglingCtrl().signalEnemyFastShotRand();
                break;
            case JugglingShotKind_Search:
                custom.jugglingCtrl().signalEnemySearchShotRand();
                break;
            }
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateJugglingAttack::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateJugglingAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
