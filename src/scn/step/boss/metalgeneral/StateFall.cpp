#include "scn/step/boss/metalgeneral/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateLanding.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateFall::StateFall(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(3);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), param._24);
}

void StateFall::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
