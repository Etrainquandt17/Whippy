#include "scn/step/boss/doubter/StateDamageL.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateAnger.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.jugglingCtrl().inactivateEnf();
    obj().model().reqScript(37);
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
    obj().soundSE().loop().stop();
    Utility::StagingBossDamageL(obj());
    obj().invincible().setPermNoFlash();
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_REFLECT);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().move().resetVelocity();
}

StateDamageL::~StateDamageL() {
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_NORMAL);
}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd() && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().doubter();
    if (obj().footState().isGround()) {
        obj().move().groundDecel(param._10);
    } else {
        obj().move().airDecelFall(param._14, param._18);
    }
}

void StateDamageL::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
}

}}}}  // namespace scn::step::boss::doubter
