#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/landiasingle/StateFormationPassMakeFireBall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/SingleWeaponCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateFormationPass.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateFormationPassMakeFireBall::StateFormationPassMakeFireBall(Enemy* enemy, StateFormationPass::Config config)
    : StateBase(enemy), mFrame(0), mConfig(config) {
    obj().model().reqScript(0xd);
    obj().move().resetVelocity();
    util::ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(0);
    if (boss.isAlive()) {
        boss::landia::Custom& custom = hel::common::DynamicCastToRef<boss::landia::Custom, boss::ICustom>(boss->custom());
        custom.singleWeaponCtrl().changeStateMoveFormationPass();
        util::ObjRefHandle<weapon::Weapon> weapon = custom.singleWeaponCtrl().weaponPtr(0);
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
