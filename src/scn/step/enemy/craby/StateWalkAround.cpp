#include "scn/step/enemy/craby/StateWalkAround.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Effect.h"
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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/craby/Custom.h"
#include "scn/step/enemy/craby/ParamData.h"
#include "scn/step/enemy/craby/StateAttack.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace craby {

StateWalkAround::StateWalkAround(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().craby();
    switch (obj().level()) {
    case 0:
        mAccel = param.mWalkAccel[0];
        break;
    case 1:
        mAccel = param.mWalkAccel[1];
        break;
    case 2:
        mAccel = param.mWalkAccel[2];
        break;
    default:
        mAccel = param.mWalkAccel[3];
        f32 dist = obj().param().common().mCliffFrontDist;
        obj().cliffChecker().changeFrontDist(dist);
        break;
    }
    obj().footState().setGround();
    obj().move().resetSpeedH();
    obj().model().reqScript(7);
    obj().model().setFrameRate(mAccel._0 / param.mWalkSpeedBase);
    mBasePosX = DynamicCastToRef<Custom, ICustom>(obj().custom()).getBasePosX();
}

StateWalkAround::~StateWalkAround() {}

void StateWalkAround::procAnim() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInAimArea()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

void StateWalkAround::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
}

void StateWalkAround::procFixPos() {
    const ParamData& param = obj().param().craby();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWallFront() || obj().cliffChecker().isCliff()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
        mBasePosX = obj().location().pos().x + param.mAroundDist * obj().target().getSign();
        DynamicCastToRef<Custom, ICustom>(obj().custom()).setBasePosX(mBasePosX);
    } else {
        f32 diff = obj().location().pos().x - mBasePosX;
        if (Math::AbsF32(diff) > param.mAroundRange) {
            obj().target().setIsRightDir(diff < 0.0f);
        }
    }
    Utility::ChkNururiTurn(obj());
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).reset();
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::craby
