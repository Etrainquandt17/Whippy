#include "scn/step/boss/lowper/StateDead.h"

#include "app/Random.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/Manager.h"
#include "scn/step/sfx/ReverseWorld.h"
#include "scn/step/sfx/ScreenFade.h"

using app::Random;
using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateDead::StateDead(Boss* boss) : StateBase(boss), mCount(0), mRotV(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().reqScript(0x17);
    custom.waftMoveCtrl().setIsValid(false);
    obj().move().resetVelocity();
    obj().flash().damage().cancel();
    obj().comp().sfxManager().reverseWorld().startAnim(0, false);
    obj().comp().screenFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0xF0 });
    obj().comp().screenFade().setFadeIn(30);
    obj().comp().objStopManager().requestStopPowerful(20);
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    mCount++;
    if (mCount == 60) {
        Vector3 pos = obj().location().pos();
        pos.y += 1.0f;
        obj().comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0x55), pos);
        u32 se[] = { 0x571, 0x571, 0x565 };
        u32 level = obj().level();
        if (level >= 3) {
            level = 2;
        }
        obj().comp().permSoundSE().start(se[level]);
        obj().dead();
        return;
    }
    if (mCount % 8 == 0) {
        Vector3 pos = obj().location().pos();
        pos.y += 1.0f;
        pos.x += 3.0f * Random::RandAF();
        pos.y += 3.0f * Random::RandAF();
        obj().comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0x7A), pos);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(4));
        obj().soundSE().normal().start(0x29B);
    }
    mRotV += obj().target().getSign();
    obj().model().rotCtrl().initRotV(mRotV);
    Vector3 offset(0.0f, 0.5f * Random::RandAF(), 0.0f);
    obj().model().setViewOffset(offset);
}

void StateDead::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.1f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.05f, 0.0001f, 0.01f);
    obj().move().airDecelFall(decel, fall);
}

void StateDead::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
