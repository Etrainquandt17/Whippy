#include "scn/step/boss/common/StateJumpAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/gigantedge/Custom.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCast;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpAttack::StateJumpAttack(Boss* boss, StateJumpAttackDesc& desc, unsigned long scriptKind)
    : StateBase(boss), mIsAttack(false), mDesc(desc) {
    obj().footState().setAir();
    obj().model().reqScript(scriptKind);
    Vector2 speed = mDesc._0;
    speed.x *= obj().target().getSign();
    obj().move().setVelocity(speed.toVector3());
}

StateJumpAttack::~StateJumpAttack() {}

void StateJumpAttack::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsAttack = !mIsAttack;
        if (mIsAttack) {
            obj().move().resetVelocity();
        }
    }
}

void StateJumpAttack::procMove() {
    if (!mIsAttack) {
        obj().move().airDecelFall(mDesc._8, mDesc._C);
    }
}

void StateJumpAttack::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        if (obj().kind() == map::BinBossKind_Gigantedge) {
            gigantedge::Custom* custom = DynamicCast<gigantedge::Custom*, ICustom>(obj().custom());
            custom->reqSwordShot(false);
        }
        obj().stateChanger().setNextState<StateLanding, Boss*, int>(objPtr(), mDesc._18);
    }
}

}}}}  // namespace scn::step::boss::common
