#include "scn/step/enemy/common/StateShootingMove.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateShootingMove::StateShootingMove(Enemy* enemy, Config config) : StateBase(enemy), mCenterX(0.0f), mVelocity() {
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
    hel::math::Direction3 dir = obj().target().getDirection3();
    if (obj().dirType() == 0) {
        dir.mFront.rotate(dir.mLeft, 0.017453292f * -config._0);
    } else {
        dir.mFront.rotate(dir.mLeft, 0.017453292f * config._0);
    }
    dir.restructFrontLeft();
    mVelocity = dir.mFront * config._4;
}

StateShootingMove::~StateShootingMove() {}

void StateShootingMove::procAnim() {}

void StateShootingMove::procMove() {
    hel::math::Vector3 velocity = mVelocity;
    if (!hel::math::Math::EqZero(mCenterX)) {
        velocity.x += obj().comp().mainCamera().getCenter().x - mCenterX;
        obj().move().setVelocity(velocity);
        gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
        obj().move().decel(decel);
    }
}

void StateShootingMove::procFixPos() {
    mCenterX = obj().comp().mainCamera().getCenter().x;
}

}
}
}
}
