#include "scn/step/boss/fattybuffer/StateStickRoofFall.h"

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

StateStickRoofFall::StateStickRoofFall(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    custom.postureCtrl().resetTarget();
    obj().move().resetVelocity();
}

StateStickRoofFall::~StateStickRoofFall() {}

void StateStickRoofFall::procAnim() {}

void StateStickRoofFall::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().airDecelFall(param._18, param._1C);
}

void StateStickRoofFall::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
