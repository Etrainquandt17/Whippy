#include "scn/step/boss/roah/StateDamageL.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateAnger.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(23);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(GUARD_TYPE_6);
    obj().effect().state().releaseAndVanish();
    obj().effect().normal().releaseAndVanish();
    custom.rotCtrl().toValid();
    custom.weaponCtrl().clearReqBuff();
    obj().model().model().nodes().at(12).setVisibilityBelow(true);
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNoForBoss(static_cast< ::scn::step::ocoll::TeamNo>(1));
    custom.weaponCtrl().requestStarInvisible();
    Utility::StagingBossDamageL(obj());
    obj().move().resetVelocity();
    if (!Utility::IsArena(obj())) {
        generateItem();
    }
}

StateDamageL::~StateDamageL() {}

void StateDamageL::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateAnger, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().roah();
    obj().move().decel(param.mDecel);
}

void StateDamageL::procFixPos() {}

// TODO: generateItem() (0x5F4 bytes) is not written: it needs scn::step::item::Desc, Manager and Item, which have no
// headers yet.

}}}}  // namespace scn::step::boss::roah
