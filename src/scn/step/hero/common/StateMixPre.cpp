#include "scn/step/hero/common/StateMixPre.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateMix.h"
#include "scn/step/ostop/Requestor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateMixPre::StateMixPre(Hero* hero)
    : StateBase(hero) {
    obj().stateChecker().setDemo(true);
    obj().model().script().start(0x29);
    obj().invincible().setPermNoFlash();
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().stateChecker().setIsForbidSpaceJump(true);
}

StateMixPre::~StateMixPre() {
    obj().stateChecker().setDemo(false);
    Utility::SetSecondMoveIsValid(obj(), true);
    obj().stateChecker().setIsForbidSpaceJump(false);
}

void StateMixPre::procAnim() {
    ostop::Requestor requestor(obj().comp());
    if (!requestor.request(static_cast<ostop::Flag>(0x11FF))) {
        return;
    }
    obj().stateChanger().setNextState<StateMix, Hero*, ::ostop::ReqHandle>(objPtr(), requestor.takeHandle());
}

}}}}  // namespace scn::step::hero::common
