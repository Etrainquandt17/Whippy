#include "scn/step/hero/fire/StateFireBreathEnd.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

StateFireBreathEnd::StateFireBreathEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().model().script().start(0xB0);
}

StateFireBreathEnd::~StateFireBreathEnd() {
}

void StateFireBreathEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateFireBreathEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateFireBreathEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
