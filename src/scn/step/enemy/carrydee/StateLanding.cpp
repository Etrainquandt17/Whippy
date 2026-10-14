#include "scn/step/enemy/carrydee/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/carrydee/Custom.h"
#include "scn/step/enemy/carrydee/StateFall.h"
#include "scn/step/enemy/carrydee/StateWait.h"
#include "scn/step/enemy/common/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateLanding::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).fixPosKey();
}

void StateLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::carrydee
