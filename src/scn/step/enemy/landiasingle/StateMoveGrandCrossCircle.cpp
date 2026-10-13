#include "scn/step/enemy/landiasingle/StateMoveGrandCrossCircle.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/SingleWeaponCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateWait.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateMoveGrandCrossCircle::StateMoveGrandCrossCircle(Enemy* enemy) : StateBase(enemy), mFrame(0), mStart(), mEnd() {
    const ParamData& param = obj().param().landiasingle();
    obj().model().reqScript(8);
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    mEnd = obj().comp().mainCamera().getCenter();
    mEnd.y += param._3c;
    switch (obj().level()) {
    case 0:
        mEnd.y += param._38;
        break;
    case 1:
        mEnd.x -= param._34;
        break;
    case 2:
        mEnd.y -= param._38;
        break;
    case 3:
        mEnd.x += param._34;
        break;
    }
    if (mEnd.x > mStart.x) {
        obj().target().setIsRightDir(true);
    } else {
        obj().target().setIsRightDir(false);
    }
}

StateMoveGrandCrossCircle::~StateMoveGrandCrossCircle() {}

void StateMoveGrandCrossCircle::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._124) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateMoveGrandCrossCircle::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._124);
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    obj().location().setPos(hel::math::Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateMoveGrandCrossCircle::procFixPos() {}

}
}
}
}
