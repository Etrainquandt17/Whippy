#include "scn/step/weapon/landiasinglegrandcross/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiasinglegrandcross/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglegrandcross {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), mIsLoop(false) {
    const Param& param = obj().param().landiaSingleGrandCross();
    obj().model().rotCtrl().initRotH(0.0f);
    obj().move().resetVelocity();
    obj().model().reqScript(0);
    obj().model().anim().setFrameRate(param._8);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x36C), 2);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x36C), 3);
    obj().soundSE().start(0x477);
}

void StateMain::procAnim() {
    if (obj().model().anim().currentG3DAnimIndex() == 0 && obj().model().anim().isAnimEnd()) {
        obj().model().reqScript(1);
        mIsLoop = true;
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {
    const Param& param = obj().param().landiaSingleGrandCross();
    if (mIsLoop) {
        obj().objColl().clearAttack();
        hel::math::Vector2 node2 = obj().model().model().nodes().at(2).worldTrans().getXY();
        hel::math::Vector2 node3 = obj().model().model().nodes().at(3).worldTrans().getXY();
        hel::math::Vector2 offset2 = node2 - obj().location().pos().getXY();
        hel::math::Vector2 offset3 = node3 - obj().location().pos().getXY();
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x211));
        obj().objColl().addAttack(0, param._0, offset2);
        obj().objColl().addAttack(0, param._0, offset3);
        obj().objColl().addAttack(0, param._4, offset2, offset3);
    }
}

}
}
}
}
