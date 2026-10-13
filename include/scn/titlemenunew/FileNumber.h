#ifndef SCN_TITLEMENUNEW_FILENUMBER_H
#define SCN_TITLEMENUNEW_FILENUMBER_H

#include "lyt/Layout.h"
#include "scn/titlemenunew/CompleteMark.h"
#include "scn/titlemenunew/FileIcon.h"
#include "types.h"

namespace info {
class AnimSyncer;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class FileNumber {
public:
    FileNumber(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, info::AnimSyncer& animSyncer);
    ~FileNumber();

    void updateFrame();
    void update(u32 file);
    void in();
    void out();
    void save();
    void show();

private:
    lyt::Layout mLayout;
    FileIcon mIcon;
    CompleteMark mCompleteMark;
    // TODO: an enum; 1 and 2 are the In and Out animations, 3 and 4 wait for the save.
    int _4B4;
    bool _4B8;
};

}}  // namespace scn::titlemenunew

#endif
