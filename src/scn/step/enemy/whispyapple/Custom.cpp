#include "scn/step/enemy/whispyapple/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/whispyapple/StateAppear.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    switch (obj().size()) {
    case 1:
    case 2:
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1c3));
        break;
    }
    obj().nururi().setValid(false);
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool Custom::onHitPointIsZero() {
    if (obj().size() != 2 && obj().vacuumReceiver().isResist()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x7a), Utility::GetCenterPos(obj()));
        obj().comp().permSoundSE().start(0x312);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        obj().dead();
        return true;
    }
    return false;
}

bool Custom::onVacuumResist() {
    if (obj().size() != 2 && obj().vacuumReceiver().isResist()) {
        hel::math::Vector2 center = Utility::GetCenterPos(obj()).getXY();
        hel::math::Vector2 attacker = obj().vacuumReceiver().getResistAttackerPos();
        int sign;
        if (attacker.x - center.x < 0.0f) {
            sign = -1;
        } else {
            sign = 1;
        }
        f32 speedH = obj().move().velocity().x + 0.005f * static_cast<f32>(sign);
        obj().move().setSpeedH(speedH);
        obj().move().setSpeedV(0.2f * (attacker.y - center.y));
    }
    return false;
}

void Custom::onProcFixPos() {}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
