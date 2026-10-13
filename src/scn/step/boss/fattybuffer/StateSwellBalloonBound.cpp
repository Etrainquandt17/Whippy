#include "scn/step/boss/fattybuffer/StateSwellBalloonBound.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardFlash.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateSwellBackJump.h"
#include "scn/step/boss/fattybuffer/StateSwellBalloonMove.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBalloonBound::StateSwellBalloonBound(Boss* boss, Kind kind, u32 count)
    : StateBase(boss), mKind(kind), mCount(count), mVelocity(boss->move().velocity()) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().guard().setType(static_cast<GuardType>(4));
    obj().flash().guard().setIsValid(true);
    if (mCount != 0) {
        mCount--;
    }
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
    switch (mKind) {
    case KIND_ROOF:
        custom.collisionCtrl().setState(CollisionCtrl::STATE_7);
        obj().model().reqScript(0x1E);
        break;
    case KIND_WALL:
        custom.collisionCtrl().setState(CollisionCtrl::STATE_8);
        obj().model().reqScript(0x1F);
        break;
    case KIND_FLOOR:
        custom.collisionCtrl().setState(CollisionCtrl::STATE_9);
        obj().model().reqScript(0x20);
        break;
    }
}

StateSwellBalloonBound::~StateSwellBalloonBound() {}

void StateSwellBalloonBound::procAnim() {
    if (obj().model().isAllEnd()) {
        if (mKind == KIND_FLOOR && mCount == 0) {
            obj().stateChanger().setNextState<StateSwellBackJump, Boss*, f32, f32>(objPtr(), 0.0f, 0.1f);
            return;
        }
        switch (mKind) {
        case KIND_ROOF:
            mVelocity.y *= -1.0f;
            break;
        case KIND_WALL:
            mVelocity.x *= -1.0f;
            obj().target().invert();
            obj().model().rotCtrl().setRotHIntoTarget();
            break;
        case KIND_FLOOR:
            mVelocity.y *= -1.0f;
            break;
        }
        obj().move().setVelocity(mVelocity);
        obj().stateChanger().setNextState<StateSwellBalloonMove, Boss*, u32>(objPtr(), mCount);
    }
}

void StateSwellBalloonBound::procMove() {}

void StateSwellBalloonBound::procFixPos() {}

}
}
}
}
