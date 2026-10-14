#include "scn/step/enemy/squishy/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateLanding.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsInWater(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(1);
    mIsInWater = custom.isInWater(true);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    const ParamData& param = obj().param().squishy();
    if (mIsInWater) {
        obj().move().resetSpeedH();
        mFrame++;
        if (mFrame == param.mJumpLandFrame[1]) {
            obj().brainCtrl().toValid();
        }
    }
}

void StateFall::procMove() {
    const ParamData& param = obj().param().squishy();
    if (mIsInWater) {
        obj().move().airDecelFall(param.mAirDecel, param.mFallWater);
    } else {
        obj().move().airDecelFall(param.mAirDecel, param.mFall);
    }
}

void StateFall::procFixPos() {
    mIsInWater = DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(true);
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::squishy
