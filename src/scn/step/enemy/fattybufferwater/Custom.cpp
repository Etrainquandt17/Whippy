#include "scn/step/enemy/fattybufferwater/Custom.h"

#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/fattybufferwater/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferwater {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().stateChanger().setNextState<StateMain, Enemy*>(&obj());
    return true;
}

bool Custom::onDamaged() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x146), obj().location().pos());
    obj().comp().permSoundSE().start(0x349);
    obj().dead();
    return true;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::fattybufferwater
