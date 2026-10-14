#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/doubter/StateSummon.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"

using app::Random;
using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

namespace {

const u32 T_SELECT_SCRIPT_TABLE[8] = { 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B };

struct Obverse {
    map::BinEnemyKind mKind;
    map::BinEnemyVariation mVariation;
    u32 _8;
};

const Obverse T_OBVERSE_TABLE[3] = {
    { static_cast<map::BinEnemyKind>(0x23), static_cast<map::BinEnemyVariation>(0x156), 2 },
    { static_cast<map::BinEnemyKind>(0x6E), static_cast<map::BinEnemyVariation>(0x157), 0 },
    { static_cast<map::BinEnemyKind>(0x6F), static_cast<map::BinEnemyVariation>(0x157), 1 },
};

}

StateSummon::StateSummon(Boss* boss, u32 kind, u32 num, map::BinEnemySize size) : StateBase(boss), mKind(kind), mNum(num), mSize(size) {
    obj().footState().setGround();
    Utility::ControlHateOnAction(obj());
    u32 script = 0x14;
    if (num < 8) {
        script = T_SELECT_SCRIPT_TABLE[num];
    }
    obj().model().reqScript(script);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateSummon::~StateSummon() {}

void StateSummon::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqEnemy();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSummon::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateSummon::procFixPos() {}

void StateSummon::reqEnemy() {
    const Param& param = obj().param().doubter();
    map::BinEnemyKind kind = static_cast<map::BinEnemyKind>(mKind);
    map::BinEnemyVariation variation = static_cast<map::BinEnemyVariation>(0);
    u32 level = 0;
    for (u32 i = 0; i < 3; i++) {
        if (kind == T_OBVERSE_TABLE[i].mKind) {
            variation = T_OBVERSE_TABLE[i].mVariation;
            level = T_OBVERSE_TABLE[i]._8;
            break;
        }
    }
    map::BinEnemySize size = mSize;
    if (size == 2 && mNum > 1) {
        size = static_cast<map::BinEnemySize>(1);
    }
    Vector2 pos = obj().location().pos().getXY();
    Vector2 offset = param._FC;
    offset.x *= obj().target().getSign();
    pos += offset;
    Vector3 speed(param._108 * Random::RandNF() + param._104, param._110 * Random::RandNF() + param._10C, 0.0f);
    speed.x *= obj().target().getSign();
    if (size == 2) {
        speed.y -= 0.5f * (speed.y - param._10C);
    }
    map::BinEnemyDirType dir = obj().target().isRightDir() ? static_cast<map::BinEnemyDirType>(3) : static_cast<map::BinEnemyDirType>(2);
    mNum--;
    enemy::Desc desc(kind, variation, level, dir, size, false, false, pos);
    ObjRefHandle<enemy::Enemy> enemy = obj().comp().enemyManager().request(desc);
    if (enemy.isAlive()) {
        enemy->move().setVelocity(speed);
        obj().soundSE().normal().start(mSize == 0 ? 0x335 : 0x328);
    }
}

}}}}  // namespace scn::step::boss::doubter
