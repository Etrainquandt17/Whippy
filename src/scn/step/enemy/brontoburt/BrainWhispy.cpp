#include "scn/step/enemy/brontoburt/BrainWhispy.h"

#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/brontoburt/StateWhispyAppear.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

BrainWhispy::BrainWhispy(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWhispy::onStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1c4));
    obj().stateChanger().setNextState<StateWhispyAppear, Enemy*>(&obj());
    return true;
}

bool BrainWhispy::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::brontoburt
