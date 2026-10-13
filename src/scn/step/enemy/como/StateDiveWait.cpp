#include "scn/step/enemy/como/StateDiveWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/ParamData.h"
#include "scn/step/enemy/como/StateBack.h"
#include "scn/step/enemy/como/StateCutFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateDiveWait::StateDiveWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {}

void StateDiveWait::procAnim() {
    const ParamData& param = obj().param().como();
    mFrame++;
    if (mFrame == param.mDiveWaitFrame) {
        obj().stateChanger().setNextState<StateBack, Enemy*>(objPtr());
    }
}

void StateDiveWait::procMove() {}

void StateDiveWait::procFixPos() {}

void StateDiveWait::procObjCollReact() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().checkCut()) {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::como
