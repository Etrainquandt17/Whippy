#include "scn/step/enemy/craby/StateWalkStraight.h"

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

namespace scn {
namespace step {
namespace enemy {
namespace craby {

StateWalkStraight::StateWalkStraight(Enemy* enemy) : StateBase(enemy) {
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
}

StateWalkStraight::~StateWalkStraight() {}

void StateWalkStraight::procAnim() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInAimArea()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

void StateWalkStraight::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
}

void StateWalkStraight::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    bool isCliff = obj().variation() == 0xd1 && Utility::ChkCliff(obj());
    if (result.isHitWallFront() || Utility::ChkNururiByDir(obj(), 0.1f) || isCliff) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).reset();
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::craby
