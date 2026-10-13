#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/weapon/needleshot/StateWait.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/NeedleParam.h"
#include "scn/step/hero/Param.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateWait::StateWait(Weapon* weapon) : StateBase(weapon), mOffsetY(0.0f) {
    mHero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().objColl().owner().rootUid());
    if (mHero.isAlive()) {
        mOffsetY = mHero->param().needle()._40;
    }
    obj().model().setVisibility(false);
    obj().mapColl().setValid(false);
}

StateWait::~StateWait() {
    obj().model().setVisibility(true);
    obj().move().decel(gobj::MoveParamDecel::Zero());
    obj().mapColl().setValid(true);
    obj().mapColl().reset();
}

void StateWait::procConstraint() {
    if (mHero.isAlive()) {
        hel::math::Vector3 pos = static_cast<const hero::Hero*>(mHero.operator->())->location().pos();
        pos.y += mOffsetY;
        obj().location().setPos(pos);
    }
}

}}}}  // namespace scn::step::weapon::needleshot
