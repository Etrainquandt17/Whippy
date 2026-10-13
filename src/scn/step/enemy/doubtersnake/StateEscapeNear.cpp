#include "scn/step/enemy/doubtersnake/StateEscapeNear.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/GroundChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/doubtersnake/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

StateEscapeNear::StateEscapeNear(Enemy* enemy) : StateBase(enemy), mFrame(0), mStartY(0.0f), mAngle(0.0f), mIsJump(false) {
    const ParamData& param = obj().param().doubtersnake();
    obj().footState().setAir();
    mStartY = obj().groundChecker().getFloorPos().y;
    obj().move().setVelocity(hel::math::Vector3(0.0f, 0.0f, param.mEscapeSpeedZ));
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().model().reqScript(3);
}

StateEscapeNear::~StateEscapeNear() {}

void StateEscapeNear::procAnim() {
    const ParamData& param = obj().param().doubtersnake();
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
    mAngle += param.mEscapeAngleSpeed;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    f32 sin = hel::math::Math::SinDegF(mAngle);
    obj().model().rotCtrl().setRotHTarget(30.0f * sin);
    if (mFrame == param.mEscapeJumpFrame) {
        mIsJump = true;
        obj().move().setSpeedV(param.mEscapeJumpSpeed);
        obj().model().reqScript(7);
        obj().model().anim().setFrameRate(param.mEscapeFrameRate);
    }
}

void StateEscapeNear::procMove() {
    const ParamData& param = obj().param().doubtersnake();
    const gobj::MoveParamFall& fall = mIsJump ? param.mEscapeJumpFall : param.mEscapeFall;
    obj().move().airDecelFall(param.mEscapeDecel, fall);
}

void StateEscapeNear::procFixPos() {
    f32 z = obj().param().doubtersnake().mEscapeZ;
    if (obj().location().pos().z > z) {
        obj().vacuumReceiver().setIsValid(false);
    }
}

}}}}  // namespace scn::step::enemy::doubtersnake
