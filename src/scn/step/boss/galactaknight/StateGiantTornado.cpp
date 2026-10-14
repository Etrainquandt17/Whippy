#include "scn/step/boss/galactaknight/StateGiantTornado.h"

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

StateGiantTornado::StateGiantTornado(Boss* boss, u32 frame, f32 speed)
    : StateBase(boss), mFrame(frame), mCount(0), mSpeed(speed) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x1D);
    obj().guard().setType(static_cast<GuardType>(2));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateGiantTornado::~StateGiantTornado() {
    obj().soundSE().loop().stop();
}

void StateGiantTornado::procAnim() {
    if (mCount < mFrame) {
        mCount++;
        if (mCount == mFrame) {
            obj().effect().state().release();
            obj().soundSE().loop().stop();
            obj().model().reqScript(0x1E);
        }
    } else {
        if (obj().scriptTrigger().get(2)) {
            reqTornado();
        }
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateGiantTornado::procMove() {}

void StateGiantTornado::procFixPos() {}

void StateGiantTornado::reqTornado() {
    const Param& param = obj().param().galactaknight();
    Vector2 pos = obj().location().pos().getXY();
    pos.x += 0.5f * obj().target().getSign();
    weapon::Desc desc(static_cast<weapon::Kind>(0x84), 0, static_cast<ostop::Flag>(8), pos,
                      Vector2(mSpeed * obj().target().getSign(), 0.0f), obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    Vector2 starPosR = param._14;
    Vector2 starPosL = starPosR;
    starPosR.x += 0.3f;
    starPosL.x -= 0.3f;
    Vector2 speed = param._24;
    starPosR.x *= obj().target().getSign();
    starPosL.x *= -obj().target().getSign();
    speed.x *= obj().target().getSign();
    Utility::GenerateStarEffect(obj(), starPosR, speed, static_cast<map::BinEnemyVariation>(0x19B));
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), starPosL, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::galactaknight
