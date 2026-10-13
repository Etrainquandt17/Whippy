#include "scn/step/boss/dubior/StateCall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateCall::StateCall(Boss* boss, u32 kind) : StateBase(boss), mKind(kind) {
    obj().footState().setAir();
    obj().model().reqScript(5);
}

StateCall::~StateCall() {}

void StateCall::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqDubiorJr();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateCall::procMove() {
    const Param& param = obj().param().dubior();
    obj().move().decel(param._4C);
}

void StateCall::procFixPos() {}

void StateCall::reqDubiorJr() {
    const Param& param = obj().param().dubior();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    hel::math::Vector2 pos1 = pos + hel::math::Vector2(param.mCallOffset.x * obj().target().getSign(), param.mCallOffset.y);
    hel::math::Vector2 pos2 = pos + hel::math::Vector2(param.mCallOffset2.x * obj().target().getSign(), param.mCallOffset2.y);
    hel::math::Vector2 space(param.mCallSpace * obj().target().getSign(), 0.0f);
    hel::math::Vector3 velocity(0.0f, 0.0f, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (mKind) {
    case 0:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos2, velocity);
        break;
    case 1:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15B), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15C), pos2, velocity);
        break;
    case 2:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15D), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15E), pos2, velocity);
        break;
    case 3:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos1 + space, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos2, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x159), pos2 + space, velocity);
        break;
    case 4:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15B), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15B), pos1 + space, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15C), pos2, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15C), pos2 + space, velocity);
        break;
    case 5:
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15D), pos1, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15D), pos1 + space, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15E), pos2, velocity);
        custom.enemyCtrl().request(static_cast<map::BinEnemyVariation>(0x15E), pos2 + space, velocity);
        break;
    }
}

}}}}  // namespace scn::step::boss::dubior
