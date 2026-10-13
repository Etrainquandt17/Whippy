#include "scn/step/boss/whispy/StateWait.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::boss::whispy
