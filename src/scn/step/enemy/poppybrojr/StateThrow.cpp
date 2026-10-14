#include "scn/step/enemy/poppybrojr/StateThrow.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/poppybrojr/Custom.h"
#include "scn/step/enemy/poppybrojr/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

StateThrow::StateThrow(Enemy* enemy) : StateBase(enemy), mFrame(0), mThrowFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    mThrowFrame = obj().param().poppybrojr().mThrowFrame;
    if (obj().variation() == 0x55) {
        mThrowFrame--;
    }
}

StateThrow::~StateThrow() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isThrowValid()) {
        custom.requestBombDead();
    }
}

void StateThrow::procAnim() {
    const ParamData& param = obj().param().poppybrojr();
    mFrame++;
    if (mFrame == mThrowFrame) {
        obj().soundSE().start(0x2a9);
        DynamicCastToRef<Custom, ICustom>(obj().custom()).changeBombState();
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateThrow::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::poppybrojr
