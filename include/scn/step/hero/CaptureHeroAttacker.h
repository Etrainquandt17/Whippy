#ifndef SCN_STEP_HERO_CAPTUREHEROATTACKER_H
#define SCN_STEP_HERO_CAPTUREHEROATTACKER_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace ocoll {

class SearchHit;

}

namespace scn {
namespace step {

class Component;

namespace hero {

class Hero;

// TODO: the enumerators.
enum CaptureHeroStateKind {
    CAPTURE_HERO_STATE_KIND_0,
    CAPTURE_HERO_STATE_KIND_F = 0xF,
    CAPTURE_HERO_STATE_KIND_10 = 0x10,
};

// TODO: members.
class CaptureHeroAttacker {
public:
    CaptureHeroAttacker(Component& component, ::ocoll::SearchHit& searchHit);
    ~CaptureHeroAttacker();

    bool chkCaptureHero();
    bool chkCaptureHero(const hel::math::Vector2& pos, f32 radius);
    bool chkCaptureHeroEnf(const hel::math::Vector2& pos, f32 radius);
    void clearCapture();
    bool isCapture() const;
    util::ObjRefHandle<Hero> heroObj();
    void reqChangeState(CaptureHeroStateKind kind);
    void reqDamage(u32 damage);
    void reqDamageSerious(u32 damage);
    void reqDamageCritical(u32 damage);
    void enableResist(bool flag);
    void disableResist(bool flag);
    u32 getResistPower() const;
    void setSuccess();
    void setAttackerPos(const hel::math::Vector3& pos);
    void setConstraintPos(const hel::math::Vector3& pos);

private:
    u32 _0[0x11];
};

}
}
}

#endif
