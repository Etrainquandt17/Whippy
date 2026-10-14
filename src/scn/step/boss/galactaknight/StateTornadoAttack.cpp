#include "scn/step/boss/galactaknight/StateTornadoAttack.h"

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
#include "scn/step/boss/galactaknight/AttackDesc.h"
#include "scn/step/boss/galactaknight/CollisionCtrl.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/LandCtrl.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateAttack.h"
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
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateTornadoAttack::StateTornadoAttack(Boss* boss)
    : StateBase(boss), mFloorY(0.0f), mSign(1.0f), mVelocity(), mAttacker(boss->comp(), boss->objColl().searchHit()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFloorY = custom.landCtrl().getFloorY();
    Vector3 pos = obj().location().pos();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    mSign = Math::Sign(heroPos.x - pos.x);
    obj().model().reqScript(0x24);
    obj().guard().setType(static_cast<GuardType>(1));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateTornadoAttack::~StateTornadoAttack() {}

void StateTornadoAttack::procAnim() {}

void StateTornadoAttack::procMove() {
    const Param& param = obj().param().galactaknight();
    Vector3 pos = obj().location().pos();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    if (Math::AbsF32(heroPos.x - pos.x) > param._60) {
        mSign = Math::Sign(heroPos.x - pos.x);
    }
    mVelocity.x = Math::Limit(param._5C * mSign + mVelocity.x, param._58);
    mVelocity.y = Math::LimitMin(mVelocity.y - param._54, -param._50);
    Vector3 next = obj().location().pos();
    next += mVelocity;
    if (next.y <= mFloorY) {
        next.y = mFloorY;
        obj().location().setPos(next);
        changeStateLanding();
    } else {
        obj().location().setPos(next);
    }
}

void StateTornadoAttack::procFixPos() {}

void StateTornadoAttack::procObjCollReact() {
    if (mAttacker.chkCaptureHero()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x23));
        mAttacker.clearCapture();
    }
}

void StateTornadoAttack::changeStateLanding() {
    const Param& param = obj().param().galactaknight();
    Utility::TurnHatedHero(obj());
    Vector2 pos = param._14;
    Vector2 speed = param._24;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    AttackDesc desc(static_cast<ScriptKind>(0x25), true);
    obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(objPtr(), desc);
}

}}}}  // namespace scn::step::boss::galactaknight
