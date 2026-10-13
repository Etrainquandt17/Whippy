#include "scn/step/enemy/brontoburt/StateFly.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mStartX(obj().location().pos().x) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    Utility::SetTargetByDirType(obj());
}

void StateFly::procMove() {
    const ParamData& param = obj().param().brontoburt();
    gobj::MoveParamAccel accel;
    switch (obj().level()) {
    case 0:
        accel = gobj::MoveParamAccel::Create(param.mFlySpeed[0], param.mFlyAccel[0], 0.001f);
        break;
    case 1:
        accel = gobj::MoveParamAccel::Create(param.mFlySpeed[1], param.mFlyAccel[1], 0.001f);
        break;
    case 2:
        accel = gobj::MoveParamAccel::Create(param.mFlySpeed[2], param.mFlyAccel[2], 0.001f);
        break;
    default:
        accel = gobj::MoveParamAccel::Create(param.mFlySpeed[3], param.mFlyAccel[3], 0.001f);
        break;
    }
    obj().move().groundAccel(obj().target().isRightDir(), accel);
}

void StateFly::procFixPos() {
    Utility::ChkNururiTurn(obj());
    hel::math::Vector3 velocity = obj().move().velocity();
    if (obj().mapColl().result().isHitWallFront()) {
        velocity.x = -velocity.x * 0.5f;
        obj().target().setIsRightDir(velocity.x > 0.0f);
    } else if (obj().variation() == 0x82 || obj().variation() == 0xf8) {
        if ((velocity.x > 0.0f && obj().location().pos().x > mStartX + obj().param().brontoburt().mFlyRange)
            || (velocity.x < 0.0f && obj().location().pos().x < mStartX - obj().param().brontoburt().mFlyRange)) {
            velocity.x = -velocity.x * 0.5f;
            obj().target().setIsRightDir(velocity.x > 0.0f);
        }
    }
    obj().move().setVelocity(velocity);
}

}}}}  // namespace scn::step::enemy::brontoburt
