#ifndef SCN_STEP_INFO_HEROSTATUS_H
#define SCN_STEP_INFO_HEROSTATUS_H

#include "effect/StdRequestor.h"
#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "nw4r/lyt/lyt_types.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "scn/step/info/HeroLifeBar.h"
#include "scn/step/info/HeroStatusIcon.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace scn {
namespace step {
namespace info {

class HeroStatus {
public:
    HeroStatus(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, hero::Kind kind, bool, bool isChallenge,
               hero::AbilityKind ability, effect::Manager& effectManager, effect::Group& effectGroup);

    void updateFrame(bool);
    bool hitTest(const hel::math::Vector2& a, const hel::math::Vector2& b);
    void setAlpha(u8 alpha);
    void setBlank(bool isBlank);
    void lifeSetLength(f32 length);
    void lifeSetRate(f32 rate);
    f32 lifeGetRate() const;
    void lifeDamage(f32 rate);
    void lifeCure(f32 rate);
    void lifeDead();
    void lifeSetIsPinch(bool isPinch, bool);
    void lifeInvincibleStart();
    void lifeInvincibleLow();
    void lifeInvincibleEnd();
    void lifeIgnoreObjStop();
    void abilitySet(hero::AbilityKind kind);
    void abilityChange(hero::AbilityKind kind);
    void toIdleState();
    void setName(hero::AbilityKind kind);
    void setNameColor(hero::AbilityKind kind);

private:
    int mState;
    bool mIsPinch;
    bool mIsInvincible;
    bool mIsBlank;
    u8 _7;
    lyt::Layout _8;
    lyt::Layout _198;
    lyt::Layout _328;
    lyt::Layout mLayout;
    HeroStatusIcon mIcon;
    HeroLifeBar mLifeBar;
    effect::StdRequestor mEffect;
    nw4r::lyt::Size _12D8;
    nw4r::lyt::Size _12E0;
    f32 _12E8;
    f32 _12EC;
    snd::SERequestor mSE;
    lyt::PaneAccessor _1364;
    hero::Kind mKind;
    bool _137C;
    bool _137D;
    lyt::PaneAccessor _1380;
    lyt::PaneAccessor _1394;
    lyt::PaneAccessor _13A8;
    lyt::PaneAccessor _13BC;
};

}
}
}

#endif
