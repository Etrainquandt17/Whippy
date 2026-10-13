#include "scn/step/boss/common/StateDash.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/common/StateDashEnd.h"
#include "scn/step/boss/common/StateDashWallHit.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateDash::StateDash(Boss* boss, StateDashDesc& desc, unsigned long scriptKind, unsigned long scriptKindWallHit, unsigned long scriptKindEnd)
    : StateBase(boss), mCount(0), mIsDash(false), mScriptKindWallHit(scriptKindWallHit), mScriptKindEnd(scriptKindEnd), mDesc(desc),
      mStartX(0.0f) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
    obj().guard().setType(mDesc._50);
    obj().move().resetVelocity();
    mStartX = obj().location().pos().x;
}

StateDash::~StateDash() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateDash::procAnim() {
    if (mIsDash) {
        mCount++;
    }
    if (mCount == mDesc._0) {
        obj().stateChanger().setNextState<StateDashEnd, Boss*, StateDashDesc, unsigned long>(objPtr(), mDesc, mScriptKindEnd);
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsDash = true;
        obj().objColl().bodyColl().initAttackType(mDesc._58);
    }
}

void StateDash::procMove() {
    if (mIsDash) {
        obj().move().groundAccel(obj().target().isRightDir(), mDesc._4);
    }
}

void StateDash::procFixPos() {
    if (StateFall::TryToChangeState(objPtr())) {
        return;
    }
    chara::MapCollResult result = obj().mapColl().result();
    if (mCount > 10 && (result._2 || obj().worldCage().isCorrected())) {
        obj().stateChanger().setNextState<StateDashWallHit, Boss*, StateDashDesc, unsigned long>(objPtr(), mDesc, mScriptKindWallHit);
    }
    if (mCount > 10 && mDesc._54) {
        f32 diff = obj().comp().mainCamera().getCenter().x - obj().location().pos().x;
        hel::math::Vector2 center = obj().comp().mainCamera().getCenter();
        f32 moved = center.x - mStartX;
        if (moved * diff < 0.0f) {
            obj().stateChanger().setNextState<StateDashEnd, Boss*, StateDashDesc, unsigned long>(objPtr(), mDesc, mScriptKindEnd);
        }
    }
}

}}}}  // namespace scn::step::boss::common
