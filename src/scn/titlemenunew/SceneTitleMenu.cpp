#define MEM_EXPLICITAUTODELETEARRAY_INLINE
#include "scn/titlemenunew/SceneTitleMenu.h"

#include "app/Application.h"
#include "app/BackupFileAccessor.h"
#include "app/HIDErrorMenu.h"
#include "app/SaveInfo.h"
#include "file/DNOption.h"
#include "file/FDGManager.h"
#include "hel/common/Color.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/debug/Print.h"
#include "lyt/LayoutContext.h"
#include "mem/Memory.h"
#include "preload/PreLoadManager.h"
#include "snd/BgmPlayer.h"
#include "snd/SoundManager.h"
#include "std/tr1/bind.h"
#include "std/tr1/reference_wrapper.h"
#include "storage/StorageManager.h"
#include "storage/UnlockState.h"
#include "storage/VolatileData.h"

using app::Application;
using app::BackupFileAccessor;
using hel::common::Color;
using hel::common::ExplicitSingleton;

namespace scn {
namespace titlemenunew {

// TODO: the rest of the unit. So far the two callers of BackupFileAccessor::updateUnlockState, and
// startFileCancelSequence, whose binds the second caller shares: a bind the unit uses only once would be expanded.
SceneTitleMenu::SceneTitleMenu(const Recipe& recipe)
    : mPreLoad()
    , mAnimSyncer()
    , mBg(ExplicitSingleton<mem::Memory>::object_->sceneHeap())
    , mFrames(ExplicitSingleton<mem::Memory>::object_->sceneHeap())
    , mModePanel(ExplicitSingleton<mem::Memory>::object_->sceneHeap(), mBg.pane("ModeSelectBaseN"),
                 mFrames.pane("FrontButtonN"), mAnimSyncer)
    , mLayout(lyt::LayoutContext("titlemenunew/Main", "FileSelectBase",
                                 ExplicitSingleton<mem::Memory>::object_->sceneHeap()))
    , mFiles(ExplicitSingleton<mem::Memory>::object_->sceneHeap())
    , mCursor(ExplicitSingleton<mem::Memory>::object_->sceneHeap())
    , mUnlockMessage(ExplicitSingleton<mem::Memory>::object_->sceneHeap(), mFrames.pane("PopupN"))
    , mHelp(ExplicitSingleton<mem::Memory>::object_->sceneHeap(), mFrames.pane("PopupN"))
    , _27A4(ExplicitSingleton<mem::Memory>::object_->sceneHeap(), false)
    , _2948(ExplicitSingleton<mem::Memory>::object_->sceneHeap(), true)
    , mFade()
    , _2B10(0)
    , _2B14(0)
    , mStart(recipe)
    , mResult(Result())
    , mSequence(ExplicitSingleton<mem::Memory>::object_->sceneHeap())
    , mSE() {
    mResult._C = false;
    BackupFileAccessor::SaveIfModified(app::SAVE_INFO_LAYOUT_KIND_1);
    ExplicitSingleton<Application>::object_->hidErrorMenu().setup(app::HIDErrorMenu::DISCONNECT_MENU_MODE_0);
    ExplicitSingleton<snd::SoundManager>::object_->bgm().stop();
    u32 file = ExplicitSingleton<Application>::object_->storageManager().volatileData()._0[2];
    for (u32 i = 0; i < 3; i++) {
        BackupFileAccessor(i).updateUnlockState();
    }
    if (recipe.mKind == START_KIND_FILE_SELECT) {
        mFrames.setFileSelect();
        mLayout.play("Wait");
    } else {
        mFrames.setModeSelect();
        mLayout.play(hel::debug::Print::HelSPrintfImpl("Select%u", file + 1));
        mLayout.setFrameToTail();
        mLayout.reflectFrameToAnim();
    }
    for (u32 i = 0; i < 3; i++) {
        if (BackupFileAccessor(i).completed()) {
            mBg.complete();
        }
    }
    mLayout.updateMatrix();
    createFiles();
    if (recipe.mKind == START_KIND_FILE_SELECT) {
        appearFiles(file);
    } else {
        showSelectedFile(file);
    }
    mCursor.frontPane(mFrames.pane("CursorN"));
    setupFileSelectCursor();
    selectFile(static_cast<FileKind>(file));
    if (recipe.mKind == START_KIND_FILE_SELECT) {
        playFileSelectBgm();
        mResult._C = true;
        _2B10 = 1;
    } else {
        mModePanel.updateItemStatus();
        mModePanel.show(file);
        setupModeSelectCursor();
        mCursor.select(recipe.mMode);
        if (recipe.mKind == START_KIND_MODE_SELECT) {
            unlockDemoOrModeSelect();
        } else if (recipe.mKind == START_KIND_THEATER_COMPLETE) {
            startTheaterCompleteSequence();
            _2B10 = 4;
        }
    }
    _2B14 = _2B10;
    _2B10 = 0;
    mFade.setColor(reinterpret_cast<const GXColor&>(recipe.mIsWhiteFadeIn ? Color::WHITE : Color::BLACK));
    mFade.setFadeIn(10);
    mFade.update();
    mBg.updateMatrix();
    mFrames.updateMatrix();
    mLayout.updateMatrix();
    Application::Object().fdgManager().preLoad("WMapCommon.dn", file::DNOption());
}

void SceneTitleMenu::startFileCancelSequence() {
    mSequence.clear();
    mSequence.call(std::tr1::bind(&Frames::back, std::tr1::ref(mFrames)))
        .wait(std::tr1::bind(&Frames::isBackEnd, std::tr1::ref(mFrames)))
        .wait(10)
        .call(std::tr1::bind(&sfx::Fade::setColor, std::tr1::ref(mFade), Color::WHITE))
        .call(std::tr1::bind(&sfx::Fade::setFadeOut, std::tr1::ref(mFade), static_cast<u32>(20)))
        .call(std::tr1::bind(&sfx::Fade::update, std::tr1::ref(mFade)))
        .wait(std::tr1::bind(&sfx::Fade::isEnd, std::tr1::ref(mFade)));
    mSequence.start();
    Application::Object().preLoadManager().cancel();
    Application::Object().fdgManager().preLoad("TitleCommon.dn", file::DNOption());
}

void SceneTitleMenu::modeSelectOrAllCompleteMovie() {
    BackupFileAccessor().updateUnlockState();
    if (BackupFileAccessor().theaterRoomCompleteState() == storage::UNLOCK_STATE_UNLOCKED) {
        mCursor.hide();
        mSequence.clear();
        mSequence.wait(60)
            .call(std::tr1::bind(&sfx::Fade::setColor, std::tr1::ref(mFade), Color::BLACK))
            .call(std::tr1::bind(&sfx::Fade::setFadeOut, std::tr1::ref(mFade), static_cast<u32>(15)))
            .call(std::tr1::bind(&sfx::Fade::update, std::tr1::ref(mFade)))
            .wait(std::tr1::bind(&sfx::Fade::isEnd, std::tr1::ref(mFade)));
        mSequence.start();
        mResult.mKind = RESULT_KIND_ALL_COMPLETE_MOVIE;
        mResult.mFile = mCursor.selectedFile();
        mResult.mMode = mCursor.selectedMode();
        _2B10 = 5;
    } else {
        focusMode(mCursor.selectedMode());
        mCursor.show();
        mCursor.focus();
        playModeSelectBgm();
        _2B10 = 6;
    }
}

}}  // namespace scn::titlemenunew
