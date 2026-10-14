#include "scn/step/enemy/metalgeneralbit/StateFly.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
}

StateFly::~StateFly() {}

void StateFly::procAnim() {}

void StateFly::procMove() {
    const ParamData& param = obj().param().metalgeneralbit();
    obj().move().decel(param.mDecel);
}

void StateFly::procFixPos() {
    Vector3 targetPos = Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
        if (boss.operator->() != 0 && boss->kind() == static_cast<map::BinBossKind>(0xb)) {
            targetPos = boss::Utility::GetHatedHeroPos(*boss.operator->());
        }
    }
    bool isRight = targetPos.x > obj().location().pos().x;
    if (isRight != obj().target().isRightDir()) {
        obj().target().setIsRightDir(isRight);
    }
}

}}}}  // namespace scn::step::enemy::metalgeneralbit
