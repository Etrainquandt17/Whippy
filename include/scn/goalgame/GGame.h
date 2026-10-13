#ifndef SCN_GOALGAME_GGAME_H
#define SCN_GOALGAME_GGAME_H

#include "effect/Group.h"
#include "g3d/Root.h"
#include "hel/common/Array.h"
#include "hel/geo/Rect.h"
#include "info/common/LowBattery.h"
#include "info/sequence/Sequence.h"
#include "lyt/Layout.h"
#include "mem/AutoHeapExp.h"
#include "scn/goalgame/GGUfoState.h"
#include "scn/goalgame/GameCtrl.h"
#include "scn/goalgame/HeroCtrl.h"
#include "scn/goalgame/Info.h"
#include "scn/goalgame/Ufo.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/info/RestPlayerPanel.h"
#include "scn/step/info/StarPanel.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/PlacementNew.h"

// TODO: util/PlacementNew.h has no isConstruct() and no access to the object
// yet, and operator[] of hel/common/Array.h is inline where the game calls a
// range-checked one. Until they change, both are specialized for what GGame holds.
namespace util {

template <>
class PlacementNew<scn::goalgame::Ufo> {
public:
    PlacementNew();
    ~PlacementNew();

    void destruct();
    bool isConstruct() const;
    scn::goalgame::Ufo* operator->() const { return mObj; }

private:
    scn::goalgame::Ufo* mObj;
    u8 mBuffer[sizeof(scn::goalgame::Ufo)];
};

}

namespace hel {
namespace common {

template <>
class Array<util::PlacementNew<scn::goalgame::Ufo>, 4> {
public:
    ~Array();

    util::PlacementNew<scn::goalgame::Ufo>& operator[](u32 index);

private:
    util::PlacementNew<scn::goalgame::Ufo> mArray[4];
};

}}  // namespace hel::common

namespace effect {
class Manager;
}

namespace scn {
namespace goalgame {

class Component;

extern const u32 FLAG_VAL_TBL[4];

class GGame {
public:
    GGame(Component& component);
    ~GGame();

    u32 checkAllUfoState(GGUfoState state);

private:
    mem::AutoHeapExp mHeap;
    g3d::Root mRoot;
    Component& mComponent;
    u32 _B4;
    u32 _B8;
    lyt::Layout mLayout;
    ::info::sequence::Sequence mSequence;
    ::effect::Manager& mEffectManager;
    ::effect::Group mEffectGroup;
    GameCtrl mGameCtrl;
    hel::common::Array<util::PlacementNew<HeroCtrl>, 4> mHero;
    hel::common::Array<util::PlacementNew<Ufo>, 4> mUfo;
    step::core::BGMController mBGM;
    step::info::RestPlayerPanel mRestPlayerPanel;
    step::info::StarPanel mStarPanel;
    snd::SERequestor mSE;
    // TODO: an sfx::Fade, 0x24 bytes; sfx/Fade.h gives it another size.
    u32 _35A00[9];
    int _35A24;
    u32 _35A28[5];
    hel::geo::Rect _35A3C;
    u32 _35A4C[11];
    util::PlacementNew<Info> mInfo;
    u32 _3600C;
    hel::common::Array<util::PlacementNew< ::info::common::LowBattery>, 4> mLowBattery;
    u32 _36690;
};

}}  // namespace scn::goalgame

#endif
