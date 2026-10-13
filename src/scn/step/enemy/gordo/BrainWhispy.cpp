#include "scn/step/enemy/gordo/BrainWhispy.h"

#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/gordo/StateWhispyAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

BrainWhispy::BrainWhispy(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWhispy::onStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1c5));
    obj().stateChanger().setNextState<StateWhispyAppear, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::gordo
