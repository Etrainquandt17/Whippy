#include "scn/step/boss/moundeath/StateTornadoChase.h"

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
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/StatePressFallStart.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
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

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateTornadoChase::StateTornadoChase(Boss* boss) : StateBase(boss), mCount(0), mWait(0), mDir() {
    obj().footState().setAir();
    obj().model().reqScript(0x1B);
    obj().move().resetVelocity();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
    mDir = hel::math::Vector3::BASIS_X * obj().target().getSign();
}

StateTornadoChase::~StateTornadoChase() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateTornadoChase::procAnim() {
    const Param& param = obj().param().moundeath();
    if (mCount < param._148) {
        mCount++;
    } else {
        obj().move().resetVelocity();
        obj().soundSE().normal().stop();
        obj().stateChanger().setNextState<StatePressFallStart, Boss*, JumpKind>(objPtr(), JUMP_KIND_1);
        return;
    }
    Utility::TurnHatedHero(obj());
    if (mWait != 0) {
        mWait--;
    }
}

void StateTornadoChase::procMove() {
    const Param& param = obj().param().moundeath();
    hel::math::Vector3 target = Utility::GetHatedHeroPos(obj());
    target.y = hel::math::Math::Min(target.y, param._150 + obj().basePos().y);
    target.y -= param._14C;
    if (target.squareDistance(obj().location().pos()) > param._154 && mWait == 0) {
        mDir = target - obj().location().pos();
        if (!mDir.isZeroLoose(0.00001f)) {
            mDir.normalize();
        } else {
            mDir = hel::math::Vector3::BASIS_X * obj().target().getSign();
        }
    }
    obj().move().accel(mDir, param._160);
}

void StateTornadoChase::procFixPos() {
    const Param& param = obj().param().moundeath();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        f32 speedX = obj().move().velocity().x;
        hel::math::Vector2 velocity(0.5f * speedX, param._158);
        obj().move().setVelocity(velocity.toVector3());
        mWait = param._16C;
        if (mDir.y > 0.0f) {
            mDir.y *= -1.0f;
        }
    }
    f32 top = param._150 + obj().basePos().y;
    if (obj().location().pos().y > top) {
        hel::math::Vector2 velocity = obj().move().velocity().getXY();
        velocity.y *= param._15C;
        obj().move().setVelocity(velocity.toVector3());
    }
}

}}}}  // namespace scn::step::boss::moundeath
