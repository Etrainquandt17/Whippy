#include "scn/step/weapon/sleepsnotbubble/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/sleepsnotbubble/Param.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace sleepsnotbubble {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    const Param& param = obj().param().sleepSnotBubble();
    f32 size = param._8;
    mcoll::detail::ShapeDiamondContext shape(hel::math::Vector2(0.0f, param._4), -size, 0.0f, size, -size, 0.0f, size);
    obj().mapColl().changeActorShape(shape);
    obj().model().rotCtrl().setRotH(param._C);
    hel::math::Vector3 scale(param._0, param._0, param._0);
    obj().model().model().nodes().at(0).localMtx().setScale(scale);
    obj().water().setForbidEffect(true);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    obj().model().rotCtrl().setRotH(obj().param().sleepSnotBubble()._C);
}

void StateMain::procMove() {}

void StateMain::procConstraint() {
    util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().objColl().owner().rootUid());
    const hero::Hero& owner = *hero.operator->();
    hel::math::Vector3 pos = owner.location().pos();
    pos.y -= obj().param().sleepSnotBubble()._10;
    obj().location().setPos(pos);
    obj().model().updateMtx();
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::sleepsnotbubble
