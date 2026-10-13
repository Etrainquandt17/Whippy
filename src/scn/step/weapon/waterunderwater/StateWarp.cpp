#include "scn/step/weapon/waterunderwater/StateWarp.h"

#include "scn/step/chara/Model.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace waterunderwater {

StateWarp::StateWarp(Weapon* weapon) : StateBase(weapon) {
    obj().model().setDrawLayerForce(static_cast<core::DrawLayerKind>(2));
    obj().model().reqScript(0);
    obj().mapColl().setValid(false);
}

StateWarp::~StateWarp() {}

void StateWarp::procAnim() {}

void StateWarp::procMove() {}

void StateWarp::procFixPos() {}

void StateWarp::procObjCollReact() {}

}
}
}
}
