#include "scn/step/enemy/walf/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/ParamData.h"
#include "scn/step/enemy/walf/StateLanding.h"
#include "scn/step/enemy/walf/StateMoveInWater.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace walf {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(1);
}

void StateFall::procAnim() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        mFrame++;
        if (mFrame == obj().param().walf().mFallInWaterFrame) {
            obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(objPtr());
        }
    }
}

void StateFall::procMove() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        obj().move().decel(obj().param().walf().mWaterDecel);
    } else {
        obj().move().airDecelFall(obj().param().common().mDecel, obj().param().walf().mFall);
    }
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walf
