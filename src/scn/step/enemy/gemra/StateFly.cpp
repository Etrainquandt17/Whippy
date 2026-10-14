#include "scn/step/enemy/gemra/StateFly.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/gemra/Custom.h"
#include "scn/step/enemy/gemra/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mWaitFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    mWaitFrame = obj().param().gemra().mFlyWaitFrame;
}

StateFly::~StateFly() {}

void StateFly::procAnim() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).updateDir();
    if (mWaitFrame == 0) {
        obj().brainCtrl().toValid();
    } else {
        mWaitFrame--;
    }
}

void StateFly::procMove() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).updatePos();
}

void StateFly::procFixPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).updateFixPos();
}

}}}}  // namespace scn::step::enemy::gemra
