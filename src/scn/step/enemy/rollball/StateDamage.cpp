#include "scn/step/enemy/rollball/StateDamage.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/rollball/Custom.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

StateDamage::StateDamage(Enemy* enemy) : StateBase(enemy) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().comp().permSoundSE().start(0x51c);
    obj().footState().setGround();
    obj().model().reqScript(5);
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    hel::math::Vector3 pos = node.worldTrans();
    f32 radius = custom.getRadius();
    switch (obj().kind()) {
    case 0x26:
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x1b1), 1);
        break;
    case 0x38:
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x1af), pos, radius);
        break;
    case 0x5b:
        radius *= 2.0f;
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x1ae), pos, radius);
        break;
    case 0x63:
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x1b0), pos, radius);
        break;
    }
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
    obj().objColl().clearBodyColl();
    obj().shadow().setVisibility(false);
}

void StateDamage::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().dead();
    }
}

}
}
}
}
