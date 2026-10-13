#include "scn/step/boss/moundeath/StatePressJumpStart.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/StatePressJump.h"
#include "scn/step/boss/moundeath/States.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StatePressJumpStart::StatePressJumpStart(Boss* boss, JumpKind kind) : StateBase(boss), mKind(kind) {
    obj().footState().setGround();
    switch (mKind) {
    case JUMP_KIND_0:
    case JUMP_KIND_1:
    case JUMP_KIND_2:
        obj().model().reqScript(9);
        break;
    case JUMP_KIND_3:
        obj().model().reqScript(0x12);
        break;
    }
    Utility::ControlHateOnAction(obj());
}

StatePressJumpStart::~StatePressJumpStart() {}

void StatePressJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        switch (mKind) {
        case JUMP_KIND_0:
        case JUMP_KIND_1:
        case JUMP_KIND_2:
            obj().stateChanger().setNextState<StatePressJump, Boss*, JumpKind>(objPtr(), mKind);
            break;
        case JUMP_KIND_3: {
            StateRollJump::Config config;
            config._0 = true;
            obj().stateChanger().setNextState<StateRollJump, Boss*, StateRollJump::Config>(objPtr(), config);
            break;
        }
        }
    }
}

void StatePressJumpStart::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().groundDecel(param._24);
}

void StatePressJumpStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
