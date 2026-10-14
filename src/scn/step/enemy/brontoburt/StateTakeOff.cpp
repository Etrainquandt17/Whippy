#include "scn/step/enemy/brontoburt/StateTakeOff.h"

#include "gobj/FootState.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/ParamData.h"
#include "scn/step/enemy/brontoburt/StateFly.h"
#include "scn/step/enemy/brontoburt/StatePursuit.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

StateTakeOff::StateTakeOff(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    Utility::SetTargetByDirType(obj());
}

void StateTakeOff::procMove() {
    const ParamData& param = obj().param().brontoburt();
    mFrame++;
    if (mFrame < param.mTakeOffFrame) {
        Vector3 pos = obj().location().pos();
        f32 height = param.mTakeOffHeight;
        f32 total = param.mTakeOffFrame;
        pos.y += 6.0f * height * mFrame * (total - mFrame) / total / total / total;
        obj().location().setPos(pos);
    } else if (mFrame > param.mTakeOffFrame + param.mTakeOffWaitFrame) {
        if (obj().variation() == 0x84 || obj().variation() == 0xfa) {
            obj().stateChanger().setNextState<StatePursuit, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateFly, Enemy*>(objPtr());
        }
    }
}

}}}}  // namespace scn::step::enemy::brontoburt
