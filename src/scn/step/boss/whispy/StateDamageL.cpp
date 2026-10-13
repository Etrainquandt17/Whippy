#include "scn/step/boss/whispy/StateDamageL.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/StateGrow.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
    Utility::StagingBossDamageL(obj());
    obj().invincible().setPermNoFlash();
    obj().model().reqScript(13);
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGrow, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {}

void StateDamageL::procFixPos() {}

}}}}  // namespace scn::step::boss::whispy
