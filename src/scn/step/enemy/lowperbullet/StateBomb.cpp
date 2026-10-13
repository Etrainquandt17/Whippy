#include "scn/step/enemy/lowperbullet/StateBomb.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"
#include "scn/step/enemy/lowperbullet/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateBomb::StateBomb(Enemy* enemy) : StateBase(enemy), mFallAccel(0.0f) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateBomb::~StateBomb() {}

void StateBomb::procAnim() {
    const ParamData& param = obj().param().lowperbullet();
    if (obj().water().isInWater()) {
        obj().move().setMoveRate(param.mWaterMoveRate);
    } else {
        obj().move().resetMoveRate();
    }
}

void StateBomb::procMove() {
    const ParamData& param = obj().param().lowperbullet();
    mFallAccel += param.mBombFallAccelStep;
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(param._8, mFallAccel, param._10);
    obj().move().airDecelFall(param.mBombDecel, fall);
}

void StateBomb::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    } else {
        if (result.isHitRoof()) {
            obj().move().setSpeedV(-0.2f * obj().move().velocity().y);
        }
        if (result.isHitWall()) {
            obj().move().setSpeedH(-0.5f * obj().move().velocity().x);
        }
    }
}

}}}}  // namespace scn::step::enemy::lowperbullet
