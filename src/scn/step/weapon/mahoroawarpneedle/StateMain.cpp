#include "scn/step/weapon/mahoroawarpneedle/StateMain.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroawarpneedle/Custom.h"
#include "scn/step/weapon/mahoroawarpneedle/StateEnd.h"
#include "snd/SERequestor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarpneedle {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(0);
    obj().model().anim().subAnimSet(0, 3, 2);
    obj().model().anim().subAnimBindPartial(0, 3);
    obj().model().anim().subAnimAccessor(0).start(true);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x437), 0);
    obj().soundSE().start(0x407);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
    obj().effect().warp().release();
}

void StateMain::procAnim() {
    Custom* custom = hel::common::DynamicCast<Custom*, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
        custom->reqChild();
    }
    if (custom->isChildDead()) {
        obj().stateChanger().setNextState<StateEnd, Weapon*>(objPtr());
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroawarpneedle
