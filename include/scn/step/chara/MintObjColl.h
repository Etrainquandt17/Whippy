#ifndef SCN_STEP_CHARA_MINTOBJCOLL_H
#define SCN_STEP_CHARA_MINTOBJCOLL_H

#include "types.h"

namespace hel {
namespace math {

class Vector2;

}
}

namespace scn {
namespace step {
namespace chara {

class ObjColl;

namespace MintObjColl {

void Register(ObjColl& obj);
void Unregister(ObjColl& obj);
void AddBodyColl(u32 id, f32 radius);
void AddBodyColl(u32 id, f32 radius, f32 x, f32 y);
void AddBodyColl(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2);
void AddBodyColl(u32 id, f32 radius, const hel::math::Vector2& offset);
void AddBodyColl(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
void ClearBodyColl();
void AddAttack(u32 id, u32 attack, f32 radius);
void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y);
void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y, f32 x2, f32 y2);
void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag);
void AddAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset);
void AddAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
void AddAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
void ClearAttack();
void ClearAttack(u32 id);
void SetAttackType(u32 id, u32 type);
void SetAttackCenter(u32 id, f32 x, f32 y);
void RenewAttack();
void AddSearchHit(u32 id, f32 radius);
void AddSearchHit(u32 id, f32 radius, f32 x, f32 y);
void AddSearchHit(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2);
void AddSearchHit(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag);
void AddSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset);
void AddSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
void AddSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
void ClearSearchHit();
void SetSearchHitTeamXlu(u32 team);
void AddSearchAttack(u32 id, f32 radius);
void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y);
void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2);
void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag);
void AddSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset);
void AddSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
void AddSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
void ClearSearchAttack();
bool IsSearchAttackCollide();
void SetBodyCollStateNormal();
void SetBodyCollStateInvincible();
void SetBodyCollStateXlu();
void SetBodyCollStateHitOnly();
void SetBodyCollStateCaptureOnly();

}
}
}
}

#endif
