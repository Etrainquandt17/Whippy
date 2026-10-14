#include "scn/step/enemy/metalgeneralball/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/metalgeneralball/Custom.h"
#include "scn/step/enemy/metalgeneralball/StateAttack.h"
#include "scn/step/enemy/metalgeneralball/StateMove.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralball {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mWaitFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().move().resetVelocity();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().signal().isValid()) {
        switch (obj().signal().get()) {
        case 1:
            if (mWaitFrame != 0) {
                mWaitFrame--;
            } else {
                obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
                obj().signal().clear();
            }
            break;
        case 2:
            if (mWaitFrame != 0) {
                mWaitFrame--;
            } else {
                obj().stateChanger().setNextState<StateMove, Enemy*>(objPtr());
                obj().signal().clear();
            }
            break;
        case 3:
            custom.reqRollExp();
            obj().dead();
            obj().signal().clear();
            break;
        }
    } else {
        mWaitFrame = obj().level();
    }
}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralball
