#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/landiasingle/StateFormationPassMakeFireBall.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/SingleWeaponCtrl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/landiasingle/StateFormationPass.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateFormationPassMakeFireBall::StateFormationPassMakeFireBall(Enemy* enemy, StateFormationPass::Config config)
    : StateBase(enemy), mFrame(0), mConfig(config) {
    obj().model().reqScript(0xd);
    obj().move().resetVelocity();
    ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(0);
    if (boss.isAlive()) {
        boss::landia::Custom& custom = DynamicCastToRef<boss::landia::Custom, boss::ICustom>(boss->custom());
        custom.singleWeaponCtrl().changeStateMoveFormationPass();
        ObjRefHandle<weapon::Weapon> weapon = custom.singleWeaponCtrl().weaponPtr(0);
        weapon->location().setPos(obj().location().centerPos());
    }
    obj().effect().state().requestN(static_cast<effect::Kind>(0x36d), 2);
}

StateFormationPassMakeFireBall::~StateFormationPassMakeFireBall() {}

void StateFormationPassMakeFireBall::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFormationPass, Enemy*, StateFormationPass::Config>(objPtr(), mConfig);
    }
}

void StateFormationPassMakeFireBall::procMove() {}

void StateFormationPassMakeFireBall::procFixPos() {}

}}}}  // namespace scn::step::enemy::landiasingle
