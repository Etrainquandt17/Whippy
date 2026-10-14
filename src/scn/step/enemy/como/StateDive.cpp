#include "scn/step/enemy/como/StateDive.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/ParamData.h"
#include "scn/step/enemy/como/StateCutFall.h"
#include "scn/step/enemy/como/StateDiveWait.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateDive::StateDive(Enemy* enemy) : StateBase(enemy), mSpeed(0.0f) {
    obj().model().reqScript(0);
    obj().soundSEState().start(0x2AA);
}

StateDive::~StateDive() {}

void StateDive::procAnim() {}

void StateDive::procMove() {
    const ParamData& param = obj().param().como();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mSpeed += param.mDiveAccel * (1.0f - mSpeed * mSpeed / (param.mDiveMaxSpeed * param.mDiveMaxSpeed));
    f32 length = custom.threadCtrl().getLength();
    length += mSpeed;
    if (length > custom.threadCtrl().getMaxLength()) {
        mSpeed = -mSpeed * param.mDiveBounceRate;
        length = custom.threadCtrl().getMaxLength();
        if (mSpeed > -param.mDiveBounceEndSpeed) {
            custom.threadCtrl().setLength(length);
            obj().stateChanger().setNextState<StateDiveWait, Enemy*>(objPtr());
            return;
        }
    }
    custom.threadCtrl().setLength(length);
}

void StateDive::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateDiveWait, Enemy*>(objPtr());
    }
}

void StateDive::procObjCollReact() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().checkCut()) {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::como
