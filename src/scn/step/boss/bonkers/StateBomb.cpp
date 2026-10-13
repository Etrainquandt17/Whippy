#include "scn/step/boss/bonkers/StateBomb.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Custom.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateBomb::StateBomb(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    obj().footState().setGround();
    if (mConfig._9) {
        obj().model().reqScript(15);
    } else {
        obj().model().reqScript(14);
    }
}

StateBomb::~StateBomb() {}

void StateBomb::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqBomb();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateBomb::procMove() {
    obj().move().groundDecel(obj().param().bonkers()._24);
}

void StateBomb::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateBomb::reqBomb() {
    const Param& param = obj().param().bonkers();
    Custom* custom = hel::common::DynamicCast<Custom*, ICustom>(obj().custom());
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos.x += param.mBombOffset.x * obj().target().getSign();
    pos.y += param.mBombOffset.y;
    hel::math::Vector2 speed(mConfig._0.x * obj().target().getSign(), mConfig._0.y);
    map::BinEnemySize size = mConfig._8 ? map::BinEnemySize_Gigant : map::BinEnemySize_Normal;
    custom->reqBomb(pos, speed, size);
}

}}}}  // namespace scn::step::boss::bonkers
