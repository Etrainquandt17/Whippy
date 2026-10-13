#include "scn/step/hero/hammer/StateTripleAttack.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/hammer/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

StateTripleAttack::StateTripleAttack(Hero* hero)
    : StateBase(hero)
    , _8(true) {
    obj().footState().setGround();
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x12F);
}

StateTripleAttack::~StateTripleAttack() {
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateTripleAttack::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        if (Utility::IsHitFrontFloor(obj())) {
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
        } else {
            obj().model().script().start(0x12E);
        }
        obj().model().scriptTrigger().clear();
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateTripleAttack::procMove() {
    hero::Utility::MoveDefaultBrake(obj());
}

void StateTripleAttack::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::hammer
