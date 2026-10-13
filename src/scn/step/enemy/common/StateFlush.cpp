#include "scn/step/enemy/common/StateFlush.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFlush::StateFlush(Enemy* enemy) : StateBase(enemy), mCount(0) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    Utility::SetTargetByDirType(obj());
}

void StateFlush::procMove() {
    const ParamData& param = obj().param().common();
    mCount++;
    if (mCount < param.mFlushFrame) {
        hel::math::Vector3 pos = obj().location().pos();
        f32 height = param.mFlushHeight;
        f32 frame = param.mFlushFrame;
        pos.y += 6.0f * height * mCount * (frame - mCount) / frame / frame / frame;
        obj().location().setPos(pos);
    } else if (mCount > param.mFlushFrame + param.mFlushWait) {
        obj().stateChanger().setNextState<StatePursuit, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
