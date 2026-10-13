#ifndef SCN_TITLEMENUNEW_FILE_H
#define SCN_TITLEMENUNEW_FILE_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "scn/titlemenunew/CompleteMark.h"
#include "scn/titlemenunew/FileIcon.h"
#include "scn/titlemenunew/FileStatus.h"
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

class File {
public:
    // TODO: name the values.
    enum No {
        NO_0,
        NO_1,
        NO_2,
    };

    File(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, No no, info::AnimSyncer& animSyncer);

    void updateFrame();
    void appear();
    void showSelected();
    void appearSelected();
    void hide();
    void disappear();
    void select();
    void deselect();
    void unlockExtra();

private:
    lyt::Layout mLayout;
    FileIcon mIcon;
    FileStatus mStatus;
    FileStatus mStatusExtra;
    CompleteMark mCompleteMark;
    bool mIsExtra;
    snd::SERequestor mSE;
};

}
}

#endif
