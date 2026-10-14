#include "scn/step/enemy/strikeboxbullet/Custom.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/strikeboxbullet/StateShot.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().effect().normal().changeLayer(static_cast<core::DrawLayerKind>(8));
    obj().nururi().setValid(false);
    obj().captureReceiver().setCanCapture(false);
    if (obj().level() == 0) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x25e), obj().model().model().g3dModel().nodeByName("TopL"));
    } else {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x25a), obj().model().model().g3dModel().nodeByName("TopL"));
    }
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

bool Custom::onDamaged() {
    obj().dead();
    return true;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::strikeboxbullet
