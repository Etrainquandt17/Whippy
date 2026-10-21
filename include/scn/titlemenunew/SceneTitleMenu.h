#ifndef SCN_TITLEMENUNEW_SCENETITLEMENU_H
#define SCN_TITLEMENUNEW_SCENETITLEMENU_H

#include "info/AnimSyncer.h"
#include "info/complete/Manager.h"
#include "info/help/Manager.h"
#include "info/sequence/Sequence.h"
#include "lyt/Layout.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/IScene.h"
#include "scn/titlemenunew/Bg.h"
#include "scn/titlemenunew/Cursor.h"
#include "scn/titlemenunew/File.h"
#include "scn/titlemenunew/FileKind.h"
#include "scn/titlemenunew/Frames.h"
#include "scn/titlemenunew/ModeKind.h"
#include "scn/titlemenunew/ModePanel.h"
#include "scn/titlemenunew/UnlockMessage.h"
#include "seq/EntryInfo.h"
#include "sfx/Fade.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace titlemenunew {

class SceneTitleMenu : public IScene {
public:
    enum StartKind {
        START_KIND_FILE_SELECT,
        START_KIND_MODE_SELECT,
        START_KIND_THEATER_COMPLETE,
    };

    enum ResultKind {
        RESULT_KIND_CANCEL,
        RESULT_KIND_MODE_DECIDED,
        RESULT_KIND_ALL_COMPLETE_MOVIE,
    };

    struct Start {
        StartKind mKind;
        ModeKind mMode;
        bool mIsWhiteFadeIn;
    };

    struct Recipe : Start {
        seq::EntryInfo mEntryInfo;
    };

    struct Result {
        ResultKind mKind;
        FileKind mFile;
        ModeKind mMode;
        bool _C;
    };

    SceneTitleMenu(const Recipe& recipe);

    Result result() const;

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneTitleMenu();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    class PreLoad {
    public:
        PreLoad();
        ~PreLoad();

    private:
        u32 _0;
    };

    void createFiles();
    void appearFiles(u32 file);
    void showSelectedFile(u32 file);
    void selectFile(FileKind kind);
    void setupFileSelectCursor();
    void setupModeSelectCursor();
    void focusMode(ModeKind kind);
    void playFileSelectBgm();
    void playModeSelectBgm();
    void unlockDemoOrModeSelect();
    void startTheaterCompleteSequence();
    void startFileCancelSequence();
    void modeSelectOrAllCompleteMovie();

    PreLoad mPreLoad;
    info::AnimSyncer mAnimSyncer;
    Bg mBg;
    Frames mFrames;
    ModePanel mModePanel;
    lyt::Layout mLayout;
    mem::ExplicitAutoDeleteArray<File, 3> mFiles;
    Cursor mCursor;
    UnlockMessage mUnlockMessage;
    info::help::Manager mHelp;
    info::complete::Manager _27A4;
    info::complete::Manager _2948;
    sfx::Fade mFade;
    int _2B10;
    int _2B14;
    Start mStart;
    Result mResult;
    info::sequence::Sequence mSequence;
    snd::SERequestor mSE;
};

}}  // namespace scn::titlemenunew

#endif
