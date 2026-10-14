#include "scn/step/enemy/blipper/StateDive.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/blipper/ParamData.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateDive::StateDive(Enemy* enemy) : StateBase(enemy), mFrame(0), mSpeedV(-0.05f), mDir(-1.0f), mRotCtrl() {
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    obj().model().rotCtrl().setRotVTarget(0.0f);
    obj().model().rotCtrl().setRotHTarget(0.0f);
}

void StateDive::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(3);
    }
}

void StateDive::procMove() {
    const ParamData& param = obj().param().blipper();
    Vector3 pos = obj().location().pos();
    if (mDir < 0.0f || ++mFrame >= param.mDiveTurnFrame) {
        mSpeedV += param.mDiveAccel * mDir;
    }
    if (mSpeedV < -param.mDiveSpeedMax) {
        mSpeedV = -param.mDiveSpeedMax;
    } else if (mSpeedV > param.mDiveSpeedMax) {
        mSpeedV = param.mDiveSpeedMax;
    }
    pos.y += mSpeedV;
    obj().location().setPos(pos);
}

void StateDive::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        mSpeedV = 0.0f;
        mDir = Math::Abs(mDir);
    } else if (obj().mapColl().result().mIsHitRoof) {
        mSpeedV = 0.0f;
        mDir = -Math::Abs(mDir);
    } else if (mDir < 0.0f &&
               obj().water().isPosInWater(Vector2(0.0f, obj().param().blipper().mDiveWaterCheckY))) {
        mSpeedV = 0.0f;
        mDir = Math::Abs(mDir);
    }
    Vector3 dir = obj().location().pos() - obj().location().prevPos();
    if (dir.isZeroLoose(0.001f)) {
        dir = Vector3(0.0f, 0.0f, 0.0f);
    } else {
        dir.normalize();
    }
    mRotCtrl.update(dir);
    obj().model().setCustomMtx(mRotCtrl.getRotMtx());
}

}}}}  // namespace scn::step::enemy::blipper
