#include "scn/step/weapon/goliathenergyball/StateThrow.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/Param.h"
#include "scn/step/weapon/goliathenergyball/StateExplode.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

StateThrow::StateThrow(Weapon* weapon) : StateBase(weapon), mLimitY(0.0f), mQuakeInterval(0) {
    const Param& param = obj().param().goliathEnergyBall();
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    obj().soundSE().start(0x365);
    mLimitY = param._4 + static_cast<const Component&>(obj().comp()).mainCamera().getViewRect()._4;
}

StateThrow::~StateThrow() {
    obj().effect().normal().release();
    obj().soundSE().stop();
}

void StateThrow::procAnim() {
    if (mQuakeInterval != 0) {
        mQuakeInterval--;
    } else {
        mQuakeInterval = 6;
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
    }
}

void StateThrow::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateThrow::procFixPos() {
    if (obj().location().pos().y < mLimitY) {
        obj().stateChanger().setNextState<StateExplode, Weapon*>(objPtr());
    }
}

}}}}  // namespace scn::step::weapon::goliathenergyball
