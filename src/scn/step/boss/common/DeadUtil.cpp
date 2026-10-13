#include "scn/step/boss/common/DeadUtil.h"

#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/ScreenFade.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

void DeadUtil::RequestDeadEffect(Boss& boss, bool isWeak) {
    hel::math::Vector2 offset = boss.param().common().mDeadEffectOffset;
    boss.comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0x128), boss.location().pos() + offset.toVector3());
    boss.comp().objStopManager().requestStopPowerful(15);
    boss.comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
    boss.comp().permSoundSE().start(0x2BA);
    boss.comp().screenFade().setColor(isWeak ? (GXColor){ 0xFF, 0xFF, 0xFF, 0x3C } : (GXColor){ 0xFF, 0xFF, 0xFF, 0xC0 });
    boss.comp().screenFade().setFadeIn(20);
}

}}}}  // namespace scn::step::boss::common
