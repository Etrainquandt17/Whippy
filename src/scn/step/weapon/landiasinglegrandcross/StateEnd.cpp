#include "scn/step/weapon/landiasinglegrandcross/StateEnd.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Anim.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiasinglegrandcross/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglegrandcross {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().landiaSingleGrandCross();
    obj().model().rotCtrl().initRotH(0.0f);
    obj().move().resetVelocity();
    obj().model().reqScript(2);
    obj().model().anim().setFrameRate(param._C);
    obj().effect().normal().release();
    obj().objColl().clearAttack();
}

void StateEnd::procAnim() {
    if (obj().model().anim().isAnimEnd()) {
        obj().dead();
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}}}}  // namespace scn::step::weapon::landiasinglegrandcross
