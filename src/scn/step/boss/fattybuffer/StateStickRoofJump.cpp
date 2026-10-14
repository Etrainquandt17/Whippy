#include "scn/step/boss/fattybuffer/StateStickRoofJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateLanding.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStickRoofJump::StateStickRoofJump(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    custom.postureCtrl().setTargetRoof();
    obj().move().resetSpeedH();
    obj().move().setSpeedV(obj().param().fattybuffer()._1A4);
}

StateStickRoofJump::~StateStickRoofJump() {}

void StateStickRoofJump::procAnim() {}

void StateStickRoofJump::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().airDecelFall(param._18, param._1C);
}

void StateStickRoofJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitRoof || result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
