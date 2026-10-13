#ifndef PAUSE_CONTEXTOPEN_H
#define PAUSE_CONTEXTOPEN_H

#include "pause/ManualKind.h"
#include "types.h"

namespace pause {

class ContextOpen {
public:
    ContextOpen();

    bool isSamePageLayout(const ContextOpen& other) const;
    ManualKind manualKind() const;
    bool commandPageOnly() const;
    bool addFriendPage() const;
    u32 getSphereCountInCurrentStage() const;

private:
    // TODO: how the members were grouped is not known. pause::PageManager::setup copies the object as two
    // pairs of words and a word, which this compiler does for two 8-byte struct members and a third member,
    // and not for six separate members.
    struct Who {
        u32 mPadChan;
        ManualKind mManualKind;
    };
    struct What {
        u32 mSphereCountInCurrentStage;
        bool mCommandPageOnly;
        bool mAddFriendPage;
    };

    Who _0;
    What _8;
    // TODO: a pause::PlayerEntryInfo.
    u32 mPlayerEntryInfo;
};

}  // namespace pause

#endif
