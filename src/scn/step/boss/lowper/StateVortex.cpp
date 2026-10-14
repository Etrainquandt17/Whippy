#include "scn/step/boss/lowper/StateVortex.h"

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
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
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
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateVortex::StateVortex(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x24);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.1f);
    custom.dataBuff().shuffleVortexBulletSpeedData();
}

StateVortex::~StateVortex() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).dataBuff().clearVortexBulletSpeedData();
}

void StateVortex::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqBullet();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateVortex::procMove() {}

void StateVortex::procFixPos() {}

void StateVortex::reqBullet() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.dataBuff().isExistVortexBulletSpeedData()) {
        Vector3 pos = obj().location().pos();
        Vector3 speed(custom.dataBuff().shiftVortexBulletSpeedData(), 0.0f, 0.0f);
        custom.enemyCtrl().request(static_cast<enemy::lowperbullet::VariationKind>(6), pos, speed, 0);
    }
}

}}}}  // namespace scn::step::boss::lowper
