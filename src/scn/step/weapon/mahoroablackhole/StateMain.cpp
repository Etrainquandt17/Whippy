#include "scn/step/weapon/mahoroablackhole/StateMain.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroablackhole/Custom.h"
#include "scn/step/weapon/mahoroablackhole/StateEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(false), mFrameRate(1.0f), mWait(60) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    hel::math::Vector3 pos = obj().location().pos();
    pos.z = -20.0f;
    obj().location().setPos(pos);
    obj().model().anim().subAnimSet(0, 3, 2);
    obj().model().anim().subAnimAccessor(0).start(true);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x3B9), 1);
    obj().model().setVisibility(false);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
    obj().effect().warp().release();
}

void StateMain::procAnim() {
    Custom* custom = hel::common::DynamicCast<Custom*, ICustom>(obj().custom());
    if (mWait != 0) {
        mWait--;
        if (mWait == 0) {
            obj().model().setVisibility(true);
            obj().model().reqScript(0);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x5EF), 1);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x3B5), 1);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x3B8), 1);
        }
        return;
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
        _8 = true;
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x3BA), 1, hel::math::Vector3(0.0f, -0.75f, 0.0f));
    }
    mFrameRate += 0.05f;
    if (mFrameRate > 5.0f) {
        mFrameRate = 5.0f;
    }
    obj().model().anim().subAnimAccessor(0).setFrameRate(mFrameRate);
    if (custom->isRequestedChangeStateToEnd()) {
        obj().stateChanger().setNextState<StateEnd, Weapon*>(objPtr());
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}
}
}
}
