#ifndef SCN_STEP_GIMMICK_POPFLOWER_POPFLOWER_H
#define SCN_STEP_GIMMICK_POPFLOWER_POPFLOWER_H

#include "hel/common/FixedString.h"
#include "hel/common/MutableArray.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vector2.h"
#include "mem/ExplicitScopedPtr.h"
#include "ocoll/Hit.h"
#include "ocoll/NodeDesc.h"
#include "ocoll/Owner.h"
#include "ocoll/SearchAttack.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/Model.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/Stop.h"
#include "scn/step/gimmick/popflower/Param.h"
#include "scn/step/gimmick/popflower/VacuumReceiver.h"
#include "scn/step/hero/Kind.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace g3d {
class Root;
}

namespace scn {
namespace step {

class Component;

namespace hero {
class Hero;
}

namespace map {
struct BinGmkGeneralEntry;
}

namespace gimmick {
namespace popflower {

class ItemGen;

class PopFlower {
public:
    enum State {
        STATE_WAIT,
        STATE_OPEN,
        STATE_OPEN_WAIT,
        STATE_DEAD,
    };

    struct HeroBodyAttack {
        HeroBodyAttack() : mOwnerId(0), mPos(hel::math::Vector2::ZERO) {}
        HeroBodyAttack(u64 ownerId, const hel::math::Vector2& pos) : mOwnerId(ownerId), mPos(pos) {}

        // TODO: implicit in the original, where hel::math::Vector2 has no assignment of its own and is copied
        // as two words.
        HeroBodyAttack& operator=(const HeroBodyAttack& other) {
            struct Words {
                u32 words[2];
            };
            mOwnerId = other.mOwnerId;
            *reinterpret_cast<Words*>(&mPos) = *reinterpret_cast<const Words*>(&other.mPos);
            return *this;
        }

        u64 mOwnerId;
        hel::math::Vector2 mPos;
    };

    PopFlower(const map::BinGmkGeneralEntry& entry, Component& component, ItemGen& itemGen, ParamAccessor<Param>& param);
    ~PopFlower();

    void registerToRoot(g3d::Root& root);
    void updateFrame();
    void objCollReact();

private:
    hel::math::Vector2 mfCenterPos() const;
    ocoll::NodeDesc mfGetOCollNodeDesc();
    void mfAddHitNode();
    void mfClearHitNode();
    void mfAddSearchAttackNode();
    void mfClearSearchAttackNode();
    void mfObjCollReactWait();
    void mfObjCollReactOpenWait();
    bool mfChkDeadBySuperAttack();
    util::ObjRefHandle<hero::Hero> mfGetAttackHero(bool) const;
    void mfUpdateHeroBodyAttacks();
    void mfClearHeroBodyAttacks();
    bool mfIsAttackBody(u32) const;
    const char* mfGetResFileName() const;
    bool mfIsInScreen();
    const char* mfHeroKindToAlphabet(hero::Kind kind);

    ParamAccessor<Param>& mParam;
    Component& mComponent;
    ItemGen& mItemGen;
    hel::common::FixedString<40> mName;
    hel::math::Vector2 mPos;
    Model mModel;
    ocoll::Owner mOwner;
    ocoll::Hit mHit;
    ocoll::SearchAttack mSearchAttack;
    hero::Kind mHeroKind;
    Effect mEffect;
    snd::SERequestor mSE;
    Stop mStop;
    State mState;
    f32 mFrameRate;
    u32 _C6C;
    mem::ExplicitScopedPtr<VacuumReceiver> mVacuumReceiver;
    hel::common::MutableArray<HeroBodyAttack, 4> mHeroBodyAttacks;
    bool _CC0;
};

}}}}  // namespace scn::step::gimmick::popflower

#endif
