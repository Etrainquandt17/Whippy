#include "scn/step/enemy/squishy/StateFall.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsInWater(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
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
    mIsInWater = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(true);
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::squishy
