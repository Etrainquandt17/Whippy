#include "scn/step/weapon/needleshot/StateStickWall.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/needleshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateStickWall::StateStickWall(Weapon* weapon) : StateBase(weapon), mAlgorithm(*weapon), mFrame(0) {
    obj().model().shake().request(static_cast<chara::ShakeKind>(0));
}

StateStickWall::~StateStickWall() {}

void StateStickWall::procAnim() {
    mFrame++;
    if (mFrame > obj().param().needleShot()._C) {
        obj().dead();
    }
}

void StateStickWall::procMove() {
    mAlgorithm.procMove();
}

void StateStickWall::procFixPos() {
    if (!obj().mapColl().isHit()) {
        obj().dead();
    } else {
        mAlgorithm.procFixPos();
    }
}

void StateStickWall::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::needleshot
