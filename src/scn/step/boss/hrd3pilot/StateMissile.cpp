#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/hrd3pilot/StateMissile.h"

#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3pilot/Custom.h"
#include "scn/step/boss/hrd3pilot/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

StateMissile::StateMissile(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(6);
}

StateMissile::~StateMissile() {}

void StateMissile::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
    if (obj().scriptTrigger().get(1)) {
        reqMissile(enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_0);
    }
    if (obj().scriptTrigger().get(2)) {
        reqMissile(enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_1);
    }
    if (obj().scriptTrigger().get(3)) {
        reqMissile(enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_2);
    }
}

void StateMissile::procMove() {}

void StateMissile::procFixPos() {}

// TODO: isRight is in r30 in the original and in r29 here.
void StateMissile::reqMissile(enemy::metalgeneralmissile::StateSpread::SpreadKind kind) {
    Vector2 pos = DynamicCastToRef<Custom, ICustom>(obj().custom()).getMissileLaunchPos().getXY();
    enemy::Desc desc(static_cast<map::BinEnemyKind>(0x7B), map::BinEnemyVariation_0, 0, static_cast<map::BinEnemyDirType>(0),
                     static_cast<map::BinEnemySize>(0), false, false, pos);
    ObjRefHandle<enemy::Enemy> missile = obj().comp().enemyManager().request(desc);
    if (missile.isAlive()) {
        Vector3 front = obj().model().model().nodes().at(0).worldRotate().mFront;
        bool isRight = front.cos(Vector3::BASIS_X * -1.0f) < 0.0f;
        missile->target().setIsRightDir(isRight);
        missile->stateChanger().setNextState<enemy::metalgeneralmissile::StateSpread, enemy::Enemy*,
                                             enemy::metalgeneralmissile::StateSpread::SpreadKind>(missile.operator->(), kind);
    }
}

}}}}  // namespace scn::step::boss::hrd3pilot
