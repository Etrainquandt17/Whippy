#include "scn/step/weapon/mahoroawarphole/StateMain.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    if (obj().variation() == 1) {
        obj().location().setPos(obj().location().pos() + hel::math::Vector3(0.0f, 0.0f, -2.5f));
        obj().model().setScale(hel::math::Vector3::ALL_ONE * 0.65f);
    }
    obj().model().reqScript(2);
    obj().model().anim().subAnimSet(0, 4, 2);
    obj().model().anim().subAnimBindPartial(0, 3);
    obj().model().anim().subAnimAccessor(0).start(true);
    obj().model().setVisibility(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x3C0), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
    obj().effect().warp().release();
}

void StateMain::procAnim() {
    if (++mFrame == 42) {
        obj().model().setVisibility(true);
        u32 script = 0;
        if (obj().variation() == 1) {
            script = 1;
        }
        obj().model().reqScript(script);
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(2);
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroawarphole
