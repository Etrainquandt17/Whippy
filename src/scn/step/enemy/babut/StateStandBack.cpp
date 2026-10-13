#include "scn/step/enemy/babut/StateStandBack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/babut/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

namespace {

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateStandBack::StateStandBack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
}

StateStandBack::~StateStandBack() {}

void StateStandBack::procAnim() {
    const ParamData& param = obj().param().babut();
    mFrame++;
    if (mFrame <= param.mStandBackFrame) {
        gobj::Move& move = obj().move();
        move.setSpeedV(param.mStandBackHeight / param.mStandBackFrame);
    } else {
        obj().move().setSpeedV(0.0f);
    }
    if (mFrame == param.mTakeOffSoundFrame) {
        obj().soundSEState().start(0x307);
    }
    if (mFrame >= param.mStandBackFrame + param.mStandBackWait) {
        obj().brainCtrl().toValid();
    }
}

void StateStandBack::procMove() {
    const ParamData& param = obj().param().babut();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airAccelFall(obj().target().isRightDir(), param.mStandBackAccel, fall);
    hel::math::Vector2 heroPos = Utility::GetNearestPlayerPos(obj());
    obj().target().setIsRightDir(heroPos.x > obj().location().pos().x);
}

void StateStandBack::procFixPos() {
    hel::math::Vector3 velocity = obj().move().velocity();
    if (t_IsHitWall(obj().mapColl().result())) {
        velocity.x = -velocity.x;
    }
    if (obj().mapColl().result().mIsHitRoof || obj().mapColl().result().mIsHitFloor) {
        velocity.y = -velocity.y;
    }
    obj().move().setVelocity(velocity);
}

}}}}  // namespace scn::step::enemy::babut
