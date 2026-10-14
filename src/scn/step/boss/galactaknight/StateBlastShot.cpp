#include "scn/step/boss/galactaknight/StateBlastShot.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateBlastShot::StateBlastShot(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x16);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateBlastShot::~StateBlastShot() {}

void StateBlastShot::procAnim() {
    if (obj().scriptTrigger().get(3)) {
        generateBlastShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBlastShot::procMove() {}

void StateBlastShot::procFixPos() {}

void StateBlastShot::generateBlastShot() {
    const Param& param = obj().param().galactaknight();
    Vector2 pos = obj().location().pos().getXY();
    pos.y += param._B4;
    Vector2 start = pos;
    start.x += param._B0 * obj().target().getSign();
    Vector2 dir = Vector2::BASIS_X;
    dir.x *= obj().target().getSign();
    dir *= param._AC;
    weapon::Desc desc(static_cast<weapon::Kind>(0x89), 0, static_cast<ostop::Flag>(8), start, pos, dir,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::galactaknight
