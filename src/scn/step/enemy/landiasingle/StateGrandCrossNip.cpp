#include "scn/step/enemy/landiasingle/StateGrandCrossNip.h"

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
#include "scn/step/enemy/landiasingle/StateGrandCrossEndWait.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateGrandCrossNip::StateGrandCrossNip(Enemy* enemy) : StateBase(enemy), mFrame(0), mMoveFrame(0), mStart(), mEnd() {
    obj().model().reqScript(7);
    obj().move().resetVelocity();
    mStart = obj().location().pos().getXY();
    f32 centerX = obj().comp().mainCamera().getCenter().x;
    f32 distance = mStart.x - centerX;
    mEnd.x = mStart.x - 2.0f * distance;
    mEnd.y = mStart.y;
}

StateGrandCrossNip::~StateGrandCrossNip() {
    obj().model().rotCtrl().initRotH(0.0f);
    Utility::TurnHero(obj());
}

void StateGrandCrossNip::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    mFrame++;
    if (mFrame >= param._138) {
        if (mMoveFrame < param._134) {
            mMoveFrame++;
        } else {
            obj().stateChanger().setNextState<StateGrandCrossEndWait, Enemy*>(objPtr());
            return;
        }
    }
    if (mFrame % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
    f32 rate = static_cast<f32>(mMoveFrame) / static_cast<f32>(param._134);
    obj().model().rotCtrl().setRotHTarget(1800.0f * rate);
}

void StateGrandCrossNip::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 rate = static_cast<f32>(mMoveFrame) / static_cast<f32>(param._134);
    obj().location().setPos(hel::math::Math::LinearInterpolation(mStart, mEnd, rate).toVector3());
}

void StateGrandCrossNip::procFixPos() {}

}
}
}
}
