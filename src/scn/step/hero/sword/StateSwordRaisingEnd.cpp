#include "scn/step/hero/sword/StateSwordRaisingEnd.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordRaisingEnd::StateSwordRaisingEnd(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().model().script().start(0x80);
}

StateSwordRaisingEnd::~StateSwordRaisingEnd() {
}

void StateSwordRaisingEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateSwordRaisingEnd::procMove() {
    Utility::MoveDefault(obj());
}

void StateSwordRaisingEnd::procFixPos() {
}

}}}}  // namespace scn::step::hero::sword
