#include "scn/step/enemy/landiasingle/StateMoveCenter.h"

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
#include "scn/step/enemy/landiasingle/StateWait.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateMoveCenter::StateMoveCenter(Enemy* enemy) : StateBase(enemy), mFrame(0), mStart(), mEnd() {
    obj().model().reqScript(8);
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    mEnd = obj().getBasePos();
    if (mEnd.x > mStart.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

StateMoveCenter::~StateMoveCenter() {}

void StateMoveCenter::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._40) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateMoveCenter::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._40);
    f32 rate = Math::SinDegF(90.0f * t);
    obj().location().setPos(Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateMoveCenter::procFixPos() {}

}}}}  // namespace scn::step::enemy::landiasingle
