#include "scn/step/weapon/deespear/StateStickWall.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/deespear/Param.h"
#include "scn/step/weapon/deespear/StateVanish.h"
#include "scn/step/weapon/deespear/Utility.h"
#include "snd/SERequestor.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

StateStickWall::StateStickWall(Weapon* weapon, f32 rot) : StateBase(weapon), mAlgorithm(*weapon), mFrame(0), mRot(rot) {
    obj().objColl().clearAttack();
    obj().model().rotCtrl().setRotV(mRot);
    obj().model().reqScript(2);
    obj().soundSE().start(0x23B);
}

StateStickWall::~StateStickWall() {}

void StateStickWall::procAnim() {
    obj().model().rotCtrl().setRotV(mRot);
    if (++mFrame == obj().param().deeSpear()._20) {
        Utility::Vanish(obj());
    } else if (mFrame >= obj().param().deeSpear()._24) {
        obj().dead();
    }
}

void StateStickWall::procMove() {
    mAlgorithm.procMove();
}

void StateStickWall::procFixPos() {
    if (!obj().mapColl().isHit()) {
        obj().stateChanger().setNextState<StateVanish, Weapon*, f32>(&obj(), mRot);
    } else {
        mAlgorithm.procFixPos();
        f32 rot = obj().target().isRightDir() ? mRot : mRot - 180.0f;
        if (Math::Abs(obj().move().velocity().y) > 0.095f
            && (Math::Abs(rot) < 20.0f || Math::Abs(rot) > 160.0f)) {
            obj().stateChanger().setNextState<StateVanish, Weapon*, f32>(&obj(), mRot);
        }
    }
}

void StateStickWall::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::deespear
