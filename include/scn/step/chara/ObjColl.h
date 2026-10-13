#ifndef SCN_STEP_CHARA_OBJCOLL_H
#define SCN_STEP_CHARA_OBJCOLL_H

#include "hel/math/Vector2.h"
#include "scn/step/ocoll/AttackType.h"
#include "types.h"

namespace ocoll {
class Attack;
class Owner;
class SearchAttack;
class SearchHit;
}

namespace scn {
namespace step {
namespace chara {

class BodyColl;

// TODO: the members are unknown.
class ObjColl {
public:
    ::ocoll::Attack& attack();
    void addBodyColl(u32 id, f32 radius);
    void addBodyColl(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addBodyColl(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addBodyColl(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void clearBodyColl();

    void addAttack(u32 id, u32 attack, f32 radius);
    void addAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset);
    void addAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addAttack(u32 id, u32 attack, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void clearAttack();
    void clearAttack(u32 id);
    u32 attackNum() const;
    void setAttackType(u32 id, ocoll::AttackType type);
    void setAttackCenter(u32 id, const hel::math::Vector2& center);
    void renewAttack();

    void addSearchHit(u32 id, f32 radius);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void clearSearchHit();
    void setSearchHitTeamXlu(u32 team);

    void addSearchAttack(u32 id, f32 radius);
    void addSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addSearchAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void clearSearchAttack();
    bool isSearchAttackCollide() const;

    void setBodyCollStateNormal();
    void setBodyCollStateInvincible();
    void setBodyCollStateXlu();
    void setBodyCollStateHitOnly();
    void setBodyCollStateCaptureOnly();
    BodyColl& bodyColl();
    ::ocoll::Owner& owner();
    ::ocoll::SearchHit& searchHit();
    ::ocoll::SearchAttack& searchAttack();
    bool isAttackCollide() const;
};

}}}  // namespace scn::step::chara

#endif
