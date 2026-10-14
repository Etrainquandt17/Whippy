#include "scn/step/boss/metalgeneral/StateMoveGround.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/ScriptKind.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateMoveGround::StateMoveGround(Boss* boss, u32 scriptKind) : StateBase(boss), mScriptKind(scriptKind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(mScriptKind);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::TurnHatedHero(obj());
    obj().move().resetVelocity();
}

StateMoveGround::~StateMoveGround() {}

void StateMoveGround::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateMoveGround::procMove() {
    const Param& param = obj().param().metalgeneral();
    gobj::MoveParamAccel accel = Utility::IsVariationExtra(obj()) ? param._BC : param._B0;
    switch (mScriptKind) {
    case SCRIPT_KIND_7:
        obj().move().groundAccel(obj().target().isRightDir(), accel);
        break;
    case SCRIPT_KIND_8:
        obj().move().groundAccel(!obj().target().isRightDir(), accel);
        break;
    }
}

void StateMoveGround::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
