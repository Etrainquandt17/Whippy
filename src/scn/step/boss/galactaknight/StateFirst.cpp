#include "scn/step/boss/galactaknight/StateFirst.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
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
#include "scn/step/boss/galactaknight/StateAppear.h"
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
using hel::geo::Rect;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

namespace {

// TODO: a stand-in, as in fattybuffer/StateFirst.cpp: the original reads the two members into temporaries ranked in
// text order, as it does for const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(boss->param().galactaknight()._F4) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    Vector3 pos = obj().basePos().toVector3();
    pos.y += param._F8;
    obj().location().setPos(pos);
    obj().model().reqScript(0x28);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    Rect rect(param._40, param._44, param._48, param._4C);
    t_Trans(rect, obj().basePos().x, obj().basePos().y);
    obj().comp().cameraController().unsetLock();
    obj().comp().cameraController().setLock(rect);
    obj().comp().cameraController().resetIntpRate();
}

StateFirst::~StateFirst() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
}

void StateFirst::procAnim() {
    if (mCount != 0) {
        mCount--;
    }
}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {
    if (mCount == 0) {
        obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::galactaknight
