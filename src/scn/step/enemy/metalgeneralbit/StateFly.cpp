#include "scn/step/enemy/metalgeneralbit/StateFly.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

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
    hel::math::Vector3 targetPos = hel::math::Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        util::ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
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
