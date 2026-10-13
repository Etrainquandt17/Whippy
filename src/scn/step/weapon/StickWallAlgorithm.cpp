#include "scn/step/weapon/StickWallAlgorithm.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

StickWallAlgorithm::StickWallAlgorithm(Weapon& weapon) : mObj(weapon) {
    mObj.objColl().clearAttack();
    pressToWall();
    chara::MapCollResult result = mObj.mapColl().result();
    if (result.mIsHitFloor) {
        mObj.landConstraint().setMode(chara::LandConstraint::MODE_2);
    } else if (result.isHitWall()) {
        mObj.landConstraint().setMode(chara::LandConstraint::MODE_3);
    } else if (result.mIsHitRoof) {
        mObj.landConstraint().setMode(chara::LandConstraint::MODE_4);
    }
}

StickWallAlgorithm::~StickWallAlgorithm() {}

void StickWallAlgorithm::procMove() {
    mObj.move().decel(gobj::MoveParamDecel::Zero());
}

void StickWallAlgorithm::procFixPos() {
    pressToWall();
}

void StickWallAlgorithm::pressToWall() {
    MapColl& mapColl = mObj.mapColl();
    if (mapColl.isHit()) {
        hel::math::Vector3 velocity = mapColl.normal().toVector3();
        velocity *= -0.1f;
        mObj.move().setVelocity(velocity);
    }
}

}}}  // namespace scn::step::weapon
