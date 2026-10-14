#include "scn/step/enemy/mahoroamagicball/State6WayShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
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

State6WayShot::State6WayShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().model().reqScript(8);
    const f32 angles[6] = { 45.0f, 90.0f, 135.0f, 315.0f, 270.0f, 225.0f };
    u32 index = obj().level();
    if (index >= 6) {
        index = 5;
    }
    Vector3 velocity = Vector3::BASIS_Y;
    velocity.rotate(Vector3::AXIS_Z, 0.017453292f * angles[index]);
    Enemy& self = obj();
    const f32& speed = Utility::IsExtra(self) ? self.param().mahoroamagicball().m6WaySpeedExtra
                                              : self.param().mahoroamagicball().m6WaySpeed;
    velocity *= speed;
    obj().move().setVelocity(velocity);
    obj().soundSE().start(0x44c);
}

State6WayShot::~State6WayShot() {}

void State6WayShot::procAnim() {}

void State6WayShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void State6WayShot::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
