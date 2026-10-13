#include "scn/arena/title/Title.h"

#include "app/Application.h"
#include "app/HIDErrorMenu.h"
#include "app/Message.h"
#include "hel/math/Vector3.h"
#include "lyt/LayoutContext.h"
#include "mem/IAllocator.h"
#include "mem/Memory.h"
#include "metafortress.h"
#include "revolution/gx/GXStruct.h"
#include "scn/arena/ArenaData.h"
#include "scn/arena/Camera.h"
#include "scn/arena/Component.h"
#include "scn/arena/ContextArena.h"
#include "sfx/Fade.h"
#include "storage/StorageManager.h"
#include "storage/VolatileData.h"

namespace scn {
namespace arena {
namespace title {

const char* TITLE_LYT_TBL[] = {
    "TitleArena",
    "TitleArenaExtra",
};

namespace {

// TODO: stands in for an inline accessor of ExplicitSingleton, which its header does not have yet.
template <class T>
inline T& tInstance() {
    return *hel::common::ExplicitSingleton<T>::object_;
}

// TODO: the later functions bind a hel::common::Color to Fade::setColor, so this most likely returns one.
inline GXColor tFadeColor() {
    GXColor color = {0, 0, 0, 255};
    return color;
}

}

// TODO: ContextArena::_B0 is declared as what ChoseData::getArenaDataPlayer
// returns, but the game reads an ArenaData there.
#define MF_FUNCTION __ct__Q43scn5arena5title5TitleFRQ33scn5arena9Component
Title::Title(Component& component)
    : MenuMain(component)
    , mRenderSet(component)
    , mHeap(tInstance<mem::Memory>().sceneHeap(), 0x18000, "Title")
    , mSE()
    , mBGM()
    , _3A0(8)
    , mLayout(lyt::LayoutContext("arena/Main", TITLE_LYT_TBL[data().gameKind()], reinterpret_cast<mem::IAllocator&>(mHeap.obj())))
    , mButtonLayout(lyt::LayoutContext("arena/Main", "TitleButton", reinterpret_cast<mem::IAllocator&>(mHeap.obj())))
    , mButtonHelp(reinterpret_cast<mem::IAllocator&>(mHeap.obj()), mLayout.pane("ButtonN"), info::common::WiiButton::KIND_0)
    , mBg(mRenderSet,
          reinterpret_cast<ArenaData&>(component.context()._B0).gameKind() == storage::ARENA_GAME_KIND_0 ? bg::desc::BG_NAME_0 : bg::desc::BG_NAME_1)
    , mSequence(reinterpret_cast<mem::IAllocator&>(mHeap.obj()))
    , _F98(0)
    , _F9C(0)
    , _FA0(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 limit;
    u32 hash;
    u32 i;

    app::HIDErrorMenu& hidErrorMenu = tInstance<app::Application>().hidErrorMenu();
    asm {
        bl      after1
        opword  MF_WORD(0x17C)
        opword  0x6C161180
        opword  MF_WORD(0x184)
        opword  0x40CE5981
    after1:
        mflr    r18
        lwz     r24, 0x8(r18)
        lwz     r16, 0x0(r18)
        stw     r16, end
        stw     r24, start
    }
    hidErrorMenu.setWatchEnable(0, true);
    hidErrorMenu.setWatchEnable(1, false);
    base = start;
    limit = end - base + 1;
    hidErrorMenu.setWatchEnable(2, false);
    hidErrorMenu.setWatchEnable(3, false);
    asm {
        bl      after2
        opword  MF_WORD(0x1F4)
        opword  0x48B44555
    after2:
        mflr    r29
        lwz     r21, 0x0(r29)
        stw     r21, expected
    }
    tInstance<app::Application>().storageManager().volatileData().mStepStageData.clearIgnoreObj();
    tInstance<app::Application>().storageManager().volatileData()._1518 = 0;
    hash = 0x811C9DC5;
    comp().setMenuState(MENU_STATE_0);
    fade().setColor(tFadeColor());
    fade().setFadeOut(1);
    if (!comp().context()._E4[0x254 - 0xE4]) {
        mBGM.request(step::core::BGM_CATEGORY_0, 0xFFFFFFFF, false);
        mBGM.setIsPlayEnable(true);
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
    }
    comp().context()._E4[0x254 - 0xE4] = false;
    mButtonLayout.setParent(mLayout.pane("TitleButtonN"));
    hash += hash << 3;
    mButtonLayout.pane("Text").setText(app::Message::TextArena("TitleStart"));
    mButtonLayout.pane("Text_00").setText(app::Message::TextArena("TitleBestTime"));
    hash ^= hash >> 11;
    if (component.getNoTitleAnimFlag()) {
        mLayout.play("Wait");
        if (crsr() == 1) {
            mButtonLayout.play("RankingChoice");
        } else {
            mButtonLayout.play("StartChoice");
        }
    } else {
        mLayout.play("TitleIn");
        mButtonLayout.play("TitleIn");
    }
    hash += hash << 15;
    switch (crsr()) {
    case 0:
        _FA0 = hash - expected != 0;
        break;
    case 1:
        _FA0 = expected == hash;
        break;
    default:
        crsr() = 0;
        _FA0 = expected == hash;
        break;
    }
    switch (reinterpret_cast<ArenaData&>(component.context()._B0).gameKind()) {
    case storage::ARENA_GAME_KIND_0:
        mRenderSet.camera().setPos(hel::math::Vector3(-30.0f, 10.0f, 225.0f));
        mRenderSet.camera().setTargetPos(hel::math::Vector3(-30.0f, 10.0f, 200.0f));
        break;
    case storage::ARENA_GAME_KIND_1:
        mRenderSet.camera().setCameraAnimFlag(expected == hash);
        break;
    }
}
#undef MF_FUNCTION

}}}  // namespace scn::arena::title
