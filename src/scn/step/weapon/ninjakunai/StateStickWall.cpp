#include "scn/step/weapon/ninjakunai/StateStickWall.h"

#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjakunai/StateVanish.h"
#include "scn/step/weapon/ninjakunai/Utility.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

StateStickWall::StateStickWall(Weapon* weapon) : StateBase(weapon), mAlgorithm(*weapon), mFrame(0) {}

StateStickWall::~StateStickWall() {}

void StateStickWall::procAnim() {
    mFrame++;
    if (mFrame > obj().param().ninjaKunai()._C) {
        obj().dead();
    } else {
        Utility::Rotate(obj());
    }
}

void StateStickWall::procMove() {
    mAlgorithm.procMove();
}

void StateStickWall::procFixPos() {
    if (!obj().mapColl().isHit()) {
        obj().stateChanger().setNextState<StateVanish, Weapon*, VanishKind>(&obj(), VANISH_KIND_DROP);
    } else {
        mAlgorithm.procFixPos();
    }
}

void StateStickWall::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::ninjakunai
