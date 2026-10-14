#include "scn/step/weapon/spearspear/StateVanish.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/spearspear/Param.h"
#include "scn/step/weapon/spearspear/Utility.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

StateVanish::StateVanish(Weapon* weapon, f32 rot) : StateBase(weapon), _8(rot), _C(0) {
    obj().mapColl().setValid(false);
    const Param& param = obj().param().spearSpear();
    obj().move().setVelocity(Vector3(param._34 * obj().target().getSign(), param._38, 0.0f));
    obj().model().rotCtrl().setRotV(_8);
    obj().model().reqScript(0);
}

StateVanish::~StateVanish() {
    obj().model().model().nodes().at(1).localMtx().reset();
}

void StateVanish::procAnim() {
    const Param& param = obj().param().spearSpear();
    _C++;
    if (_C >= param._44) {
        obj().dead();
    } else {
        if (_C == param._40) {
            Utility::Vanish(obj());
        }
        _8 -= param._3C * obj().target().getSign();
        if (_8 >= 360.0f) {
            _8 -= 360.0f;
        }
        if (_8 < 0.0f) {
            _8 += 360.0f;
        }
        obj().model().rotCtrl().setRotV(_8);
    }
}

void StateVanish::procMove() {
    const Param& param = obj().param().spearSpear();
    obj().move().airDecelFall(param._10, param._14);
}

void StateVanish::procFixPos() {}

void StateVanish::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::spearspear
