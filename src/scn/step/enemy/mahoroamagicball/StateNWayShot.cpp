#define HEL_MATH_VECTOR3_COPY_CONSTRUCTOR_OUT_OF_LINE

#include "scn/step/enemy/mahoroamagicball/StateNWayShot.h"

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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/mahoroamagicball/ParamData.h"
#include "snd/SERequestor.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

namespace {

const ParamData::NWay& t_param(const Enemy& enemy) {
    return Utility::IsExtra(enemy) ? enemy.param().mahoroamagicball().mNWayExtra : enemy.param().mahoroamagicball().mNWay;
}

}

StateNWayShot::StateNWayShot(Enemy* enemy, const Vector3& dir) : StateBase(enemy), mFrame(1), mDir(dir) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().model().reqScript(8);
    obj().move().resetVelocity();
    mFrame = obj().level() * t_param(obj()).mInterval + 1;
}

StateNWayShot::~StateNWayShot() {}

void StateNWayShot::procAnim() {
    if (mFrame != 0 && --mFrame == 0) {
        Vector3 velocity = mDir * t_param(obj()).mSpeed;
        obj().move().setVelocity(velocity);
        obj().soundSE().start(0x436);
    }
}

void StateNWayShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateNWayShot::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
