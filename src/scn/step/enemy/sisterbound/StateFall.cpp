#include "scn/step/enemy/sisterbound/StateFall.h"

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
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sisterbound/ParamData.h"
#include "snd/SERequestor.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFallAdd(0.0f) {
    obj().footState().setAir();
    obj().move().resetSpeedV();
    mSpeedH = Math::AbsF32(obj().move().velocity().x);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
        obj().model().anim().setFrameRate(obj().param().sisterbound().mLandingFrameRate);
    }
}

void StateFall::procMove() {
    const ParamData& param = obj().param().sisterbound();
    mFallAdd += param.mFallAccel;
    obj().move().airAccelFall(obj().target().isRightDir(), gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f),
                              gobj::MoveParamFall::Create(param.mFall._0, param.mFall._4 + mFallAdd, param.mFall._8));
}

void StateFall::procFixPos() {
    if (obj().variation() != 0x3d) {
        Utility::ChkNururiTurn(obj());
        if (obj().mapColl().result()._2) {
            obj().target().invert();
        }
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::sisterbound
