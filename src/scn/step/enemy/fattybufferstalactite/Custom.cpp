#include "scn/step/enemy/fattybufferstalactite/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/fattybufferstalactite/StateAppear.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().objColl().addBodyColl(0, 0.65f * obj().charaParam()._2c, Vector2(0.0f, 0.5f));
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        return false;
    }
    obj().deadWithEffect();
    return true;
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x143), obj().location().pos());
    obj().comp().permSoundSE().start(0x360);
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::fattybufferstalactite
