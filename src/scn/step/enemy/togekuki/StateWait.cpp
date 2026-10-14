#include "scn/step/enemy/togekuki/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/togekuki/ParamData.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
}

void StateWait::procMove() {
    const ParamData& param = obj().param().togekuki();
    obj().move().airDecelFall(param.mDecel, param.mFall);
    Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    bool isRight = playerPos.x > obj().location().pos().x;
    if (isRight != obj().target().isRightDir()) {
        mFrame++;
        if (mFrame == param.mTurnFrame) {
            obj().target().setIsRightDir(isRight);
        }
    } else {
        mFrame = 0;
    }
}

}}}}  // namespace scn::step::enemy::togekuki
