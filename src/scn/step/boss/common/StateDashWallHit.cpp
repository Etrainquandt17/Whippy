#include "scn/step/boss/common/StateDashWallHit.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateDashWallHit::StateDashWallHit(Boss* boss, StateDashDesc& desc, unsigned long scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setAir();
    obj().model().reqScript(scriptKind);
    Vector2 pos(mDesc._2C.x * obj().target().getSign(), mDesc._2C.y);
    Vector2 speed(mDesc._34.x * obj().target().getSign(), mDesc._34.y);
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarPuff);
    const Direction3& front =
        obj().target().isRightDir() ? Direction3::FRONT_TO_LEFT : Direction3::FRONT_TO_RIGHT;
    // TODO: the implicit copy constructor in the original; the shared header declares one out of line.
    Direction3 dir(front.mFront, front.mUp, front.mLeft);
    obj().effect().normal().requestPD(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3(), dir);
    Vector3 velocity(mDesc._24.x * obj().target().getSign(), mDesc._24.y, 0.0f);
    obj().move().setVelocity(velocity);
}

StateDashWallHit::~StateDashWallHit() {}

void StateDashWallHit::procAnim() {}

void StateDashWallHit::procMove() {
    obj().move().airDecelFall(mDesc._14, mDesc._18);
}

void StateDashWallHit::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    Vector3 velocity = obj().move().velocity();
    if (velocity.y < 0.0f && result.mIsHitFloor) {
        if (mDesc._3C) {
            Vector2 pos(mDesc._40.x * obj().target().getSign() * -1.0f, mDesc._40.y);
            Vector2 speed(mDesc._48.x * obj().target().getSign() * -1.0f, mDesc._48.y);
            Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        }
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::common
