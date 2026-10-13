#ifndef SCN_STEP_CHARA_OBJCOLLLITE_H
#define SCN_STEP_CHARA_OBJCOLLLITE_H

#include "hel/math/Vector2.h"
#include "ocoll/Owner.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/ocoll/Flag.h"
#include "types.h"

namespace ocoll {
class Attack;
class Hit;
class Owner;
class SearchHit;
}

namespace scn {
namespace step {
namespace chara {

// TODO: members. The hit and the attack are util::PlacementNew objects, whose pointers are all that is known.
class ObjCollLite {
public:
    void addHit(u32 id, f32 radius);
    void addHit(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void clearHit();
    void clearAttack();
    void renewAttack();
    void setAttackCenter(u32 id, const hel::math::Vector2& center);
    bool isAttackCollide() const;
    void addAttack(u32 id, f32 radius);
    void addAttack(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addAttack(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void setAttackType(ocoll::AttackType type);
    bool isAttackCollideMain() const;
    void addAttackSub(u32 id, f32 radius);
    void addAttackSub(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addAttackSub(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void setAttackTypeSub(ocoll::AttackType type);
    bool isAttackCollideSub() const;
    void addSearchHit(u32 id, f32 radius);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2);
    void addSearchHit(u32 id, f32 radius, const hel::math::Vector2& offset, const hel::math::Vector2& offset2, bool flag);
    void clearSearchHit();
    bool isCollideSearchHit() const;
    void setSearchHitFlagXlu(ocoll::Flag flag);
    ::ocoll::Owner& owner() { return *reinterpret_cast< ::ocoll::Owner*>(_0[2]); }

    // TODO: a util::PlacementNew object behind the attack; only its pointer at 0x6FC is known.
    ::ocoll::SearchHit& searchHit() { return *reinterpret_cast< ::ocoll::SearchHit**>(this)[0x6FC / 4]; }

    ::ocoll::Hit& hit() { return *mHit; }
    ::ocoll::Attack& attack() { return *mAttack; }
    const ::ocoll::Attack& attack() const { return *mAttack; }

private:
    u32 _0[0xF];
    ::ocoll::Hit* mHit;
    u32 _40[0x112];
    ::ocoll::Attack* mAttack;
};

}}}  // namespace scn::step::chara

#endif
