#include "scn/step/enemy/strikeboxbullet/Custom.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/strikeboxbullet/StateShot.h"
#include "snd/SERequestor.h"

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

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
