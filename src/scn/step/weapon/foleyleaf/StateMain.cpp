#include "scn/step/weapon/foleyleaf/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/foleyleaf/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace foleyleaf {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0.0f) {
    const Param& param = obj().param().foleyLeaf();
    obj().model().reqScript(1);
    obj().objColl().clearAttack();
    obj().objColl().clearHit();
    const mcoll::detail::ShapeDiamondContext& shape = mcoll::detail::ShapeDiamondContext::CreateBaseBottom(param._10, param._14, param._14);
    obj().mapColl().changeActorShape(shape);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().model().rotCtrl().setValid(false);
    obj().move().setSpeedV(obj().param().foleyLeaf()._C);
}

void StateMain::procMove() {
    bool isRight = obj().variation() == 0;
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airAccelFall(isRight, obj().param().foleyLeaf()._0, fall);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x124), obj().location().pos());
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::foleyleaf
