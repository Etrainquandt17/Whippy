#include "scn/step/enemy/kabu/BrainGrandLowper.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().model().rotCtrl().initRotH(0.0f);
    obj().model().rotCtrl().setValid(false);
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

void BrainGrandLowper::update() {
    Utility::ChkCliffTurn(obj());
}

}
}
}
}
