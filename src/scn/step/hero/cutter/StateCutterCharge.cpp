#include "scn/step/hero/cutter/StateCutterCharge.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/cutter/StateCutterThrowLong.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterCharge::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isHold(0x20)) {
        hero->stateChanger().setNextState<StateCutterCharge, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterCharge::StateCutterCharge(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , _C(true) {
    obj().model().script().start(0x97);
    obj().model().modelRotCtrl().setRotHIntpRate(0.5f);
    obj().soundSE()._78.start(0x149);
    obj().piggyback().setEnableReceive(true);
}

StateCutterCharge::~StateCutterCharge() {
    hel::math::Vector3 scale = hel::math::Vector3::ALL_ONE;
    obj().model().model().nodes().at(4).localMtx().setScale(scale);
    obj().model().modelRotCtrl().resetRotIntpRate();
}

void StateCutterCharge::procAnim() {
    mFrame++;
    f32 rate = 1.0f;
    switch (mFrame) {
    case 0x28:
        rate = 2.0f;
        break;
    case 0x29:
        rate = 2.2f;
        break;
    case 0x2A:
        rate = 1.8f;
        break;
    }
    if (mFrame >= 0x2B) {
        rate = 1.5f;
    }
    hel::math::Vector3 scale = hel::math::Vector3::ALL_ONE * rate;
    obj().model().model().nodes().at(4).localMtx().setScale(scale);
    if (mFrame == 0x28) {
        hero::Effect& effect = obj().effect();
        effect._58.requestND(static_cast<effect::Kind>(0x4AC), 0, obj().target().getDirection3());
        obj().soundSE()._4.start(0x14D);
    }
    if (!obj().hid().isHold(0x20)) {
        if (mFrame >= 0x28) {
            obj().stateChanger().setNextState<StateCutterThrowLong, Hero*>(objPtr());
        } else {
            Utility::ChangeStateWaitOrFall(obj());
        }
    }
}

void StateCutterCharge::procMove() {
    if (obj().footState().isGround()) {
        Utility::UpdateMoveTarget(obj());
        Utility::MoveDefaultBrake(obj());
    } else {
        Utility::MoveDefault(obj());
    }
}

void StateCutterCharge::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
