#include "scn/step/boss/metalgeneral/StateBackStep.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateBackStep::StateBackStep(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xA);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().setVelocity(Vector3(param._D4 * obj().target().getSign(), param._D8, 0.0f));
}

StateBackStep::~StateBackStep() {}

void StateBackStep::procAnim() {}

void StateBackStep::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().airDecelFall(param._DC, param._E0);
}

void StateBackStep::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().soundSE().normal().start(0x3DE);
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
