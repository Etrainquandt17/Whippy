#include "scn/step/boss/common/CollUtil.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

void CollUtil::SetBodyCollDefault(Boss& boss, u32 id, f32 radius, hel::math::Vector2 offset) {
    chara::BodyColl& bodyColl = boss.objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1AB));
    boss.objColl().addBodyColl(id, radius, offset);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_2);
}

void CollUtil::SetBodyCollDefault(Boss& boss, u32 id, f32 radius, hel::math::Vector2 offset, hel::math::Vector2 offset2) {
    chara::BodyColl& bodyColl = boss.objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1AB));
    boss.objColl().addBodyColl(id, radius, offset, offset2);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_2);
}

}
}
}
}
