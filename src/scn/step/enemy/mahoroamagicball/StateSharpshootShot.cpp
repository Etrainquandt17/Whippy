#include "scn/step/enemy/mahoroamagicball/StateSharpshootShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
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

StateSharpshootShot::StateSharpshootShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().model().reqScript(8);
    Vector3 target = Utility::GetNearestPlayerPos(obj()).toVector3();
    Vector3 diff = target - obj().location().pos();
    Vector3 dir = -Vector3::BASIS_Y;
    if (!diff.isZeroLoose(0.00001f)) {
        dir = diff.getNormalized();
    }
    Enemy& self = obj();
    const f32& speed = Utility::IsExtra(self) ? self.param().mahoroamagicball().mSharpshootSpeedExtra
                                              : self.param().mahoroamagicball().mSharpshootSpeed;
    obj().move().setVelocity(dir * speed);
    obj().soundSE().start(0x436);
}

StateSharpshootShot::~StateSharpshootShot() {}

void StateSharpshootShot::procAnim() {}

void StateSharpshootShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateSharpshootShot::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
