#ifndef SCN_TITLEMENUNEW_MODEPANEL_H
#define SCN_TITLEMENUNEW_MODEPANEL_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/titlemenunew/FileNumber.h"
#include "scn/titlemenunew/FileStatus.h"
#include "scn/titlemenunew/Help.h"
#include "scn/titlemenunew/IModeButton.h"
#include "scn/titlemenunew/ModeKind.h"
#include "scn/titlemenunew/Option.h"
#include "scn/titlemenunew/SubGame.h"
#include "scn/titlemenunew/TheArena.h"
#include "scn/titlemenunew/UnlockKind.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace info {
class AnimSyncer;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class ModePanel {
public:
    ModePanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, const lyt::PaneAccessor& pane,
              info::AnimSyncer& animSyncer);

    void updateFrame();
    void show(u32 file);
    void appear(u32 file);
    void disappear(u32 file);
    bool isAnimEnd() const;
    void focus(ModeKind kind);
    void unfocus(ModeKind kind);
    void decide(ModeKind kind);
    void startUnlock(UnlockKind kind);
    bool isUnlockAnimEnd(UnlockKind kind) const;
    lyt::PaneAccessor cursorParent(ModeKind kind);
    void updateItemStatus();
    void restoreFrontButton();
    IModeButton* modeButton(UnlockKind kind);
    IModeButton* modeButton(ModeKind kind);
    void bringToFront(IModeButton& button);
    FileNumber& fileNumber();

private:
    lyt::Layout mLayout;
    FileNumber mFileNumber;
    mem::ExplicitAutoDeleteArray<FileStatus, 3> mFiles;
    mem::ExplicitAutoDeleteArray<SubGame, 2> mSubGames;
    mem::ExplicitAutoDeleteArray<TheArena, 3> mArenas;
    mem::ExplicitAutoDeleteArray<Option, 3> mOptions;
    Help mHelp;
    snd::SERequestor mSE;
    lyt::PaneAccessor _8A0;
    IModeButton* _8B4;
    lyt::PaneAccessor _8B8;
};

}
}

#endif
