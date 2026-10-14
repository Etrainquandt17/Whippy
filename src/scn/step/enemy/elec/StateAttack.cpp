#include "scn/step/enemy/elec/StateAttack.h"

#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/elec/ParamData.h"
#include "scn/step/enemy/elec/StateChase.h"
#include "scn/step/ocoll/AttackType.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0.0f) {
    obj().model().reqScript(10);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x1a2));
}

StateAttack::~StateAttack() {
    obj().objColl().bodyColl().unsetAttackTypeOver();
}

void StateAttack::procAnim() {
    f32 end = static_cast<f32>(obj().param().elec().mAttackEndFrame);
    mFrame += 1.0f;
    if (mFrame > end) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::elec
