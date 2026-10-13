#include "scn/step/enemy/metalgeneralbit/StateAppear.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "scn/step/enemy/metalgeneralbit/StateFly.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mFrame(0), mWaitFrame(0), mIsAppearEnd(false) {
    const ParamData& param = obj().param().metalgeneralbit();
    obj().footState().setAir();
    obj().model().reqScript(7);
    if (obj().level() == 0) {
        mWaitFrame = param.mWaitFrameBase + app::Random::Rand(param.mWaitFrameRand);
    } else {
        mWaitFrame = app::Random::Rand(param.mWaitFrameSuper);
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
