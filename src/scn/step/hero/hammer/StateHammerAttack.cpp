#include "scn/step/hero/hammer/StateHammerAttack.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/hammer/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

StateHammerAttack::StateHammerAttack(Hero* hero)
    : StateBase(hero)
    , mIsSwing(true) {
    obj().footState().setGround();
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x12C);
}

StateHammerAttack::~StateHammerAttack() {
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateHammerAttack::procAnim() {
    if (mIsSwing) {
        if (obj().model().isAllEnd()) {
            if (Utility::IsHitFrontFloor(obj())) {
                obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
                obj().model().script().start(0x12D);
            } else {
                obj().model().script().start(0x12E);
            }
            mIsSwing = false;
        }
    } else if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateHammerAttack::procMove() {
    hero::Utility::MoveDefaultBrake(obj());
}

void StateHammerAttack::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
