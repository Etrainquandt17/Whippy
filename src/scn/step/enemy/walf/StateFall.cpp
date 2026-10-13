#include "scn/step/enemy/walf/StateFall.h"

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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/ParamData.h"
#include "scn/step/enemy/walf/StateLanding.h"
#include "scn/step/enemy/walf/StateMoveInWater.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(1);
}

void StateFall::procAnim() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
        mFrame++;
        if (mFrame == obj().param().walf().mFallInWaterFrame) {
            obj().stateChanger().setNextState<StateMoveInWater, Enemy*>(objPtr());
        }
    }
}

void StateFall::procMove() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater()) {
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
