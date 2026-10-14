#include "scn/step/enemy/metalgeneralbit/StateAppear.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "scn/step/enemy/metalgeneralbit/StateFly.h"
#include "snd/SERequestor.h"

using app::Random;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mFrame(0), mWaitFrame(0), mIsAppearEnd(false) {
    const ParamData& param = obj().param().metalgeneralbit();
    obj().footState().setAir();
    obj().model().reqScript(7);
    if (obj().level() == 0) {
        mWaitFrame = param.mWaitFrameBase + Random::Rand(param.mWaitFrameRand);
    } else {
        mWaitFrame = Random::Rand(param.mWaitFrameSuper);
    }
    obj().soundSE().start(0x3f2);
}

StateAppear::~StateAppear() {}

void StateAppear::procAnim() {
    if (obj().model().isAllEnd()) {
        mIsAppearEnd = true;
    }
    if (mIsAppearEnd) {
        if (mFrame == 0) {
            obj().model().reqScript(4);
        }
        if (mFrame == mWaitFrame) {
            obj().stateChanger().setNextState<StateFly, Enemy*>(objPtr());
        } else {
            mFrame++;
        }
    }
}

void StateAppear::procMove() {
    const ParamData& param = obj().param().metalgeneralbit();
    obj().move().decel(param.mDecel);
}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralbit
