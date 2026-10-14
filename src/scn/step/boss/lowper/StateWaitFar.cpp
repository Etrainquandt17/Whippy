#include "scn/step/boss/lowper/StateWaitFar.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateWaitFar::StateWaitFar(Boss* boss) : StateBase(boss), mPos(), _10(0.0f), _14(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    mPos = obj().basePos();
    mPos.y += 4.0f;
    obj().brainCtrl().toValid();
    obj().model().reqScript(0);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.waftMoveCtrl().setMoveIntpRate(param._18);
    custom.waftMoveCtrl().setWaveWidth(param._14);
}

StateWaitFar::~StateWaitFar() {}

void StateWaitFar::procAnim() {}

void StateWaitFar::procMove() {}

void StateWaitFar::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
