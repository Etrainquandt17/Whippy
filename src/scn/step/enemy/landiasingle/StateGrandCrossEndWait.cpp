#include "scn/step/enemy/landiasingle/StateGrandCrossEndWait.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/Color.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
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
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/landiasingle/Custom.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateWait.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateGrandCrossEndWait::StateGrandCrossEndWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(7);
    obj().move().resetVelocity();
    custom.setFlagActionEnd();
    obj().model().rotCtrl().setValid(false);
}

StateGrandCrossEndWait::~StateGrandCrossEndWait() {
    obj().model().unsetCustomMtx();
    obj().model().rotCtrl().setValid(true);
}

void StateGrandCrossEndWait::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._140) {
        mFrame++;
        f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._140);
        f32 rate = 1.5f * t + t * (-0.5f * t * t);
        setCustomMtx(rate);
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateGrandCrossEndWait::procMove() {}

void StateGrandCrossEndWait::procFixPos() {}

// TODO: the original loads the y of each offset ahead of the vector's address and the two zeros (three lines each).
void StateGrandCrossEndWait::setCustomMtx(f32 rate) {
    hel::math::Direction3 dir;
    dir.mFront = hel::math::Vector3::BASIS_Z;
    dir.mFront.rotate(hel::math::Vector3::AXIS_X, 0.017453292f * (-360.0f * rate));
    dir.mLeft = hel::math::Vector3::BASIS_X;
    dir.restructFrontLeft();
    hel::math::Matrix34 toCenter = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, obj().location().toCenter().y, 0.0f));
    hel::math::Matrix34 fromCenter = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, -obj().location().toCenter().y, 0.0f));
    hel::math::Matrix34 rot(dir, hel::math::Vector3::ZERO);
    obj().model().setCustomMtx(toCenter * rot * fromCenter);
}

}}}}  // namespace scn::step::enemy::landiasingle
