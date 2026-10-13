#ifndef SCN_TITLEMENUNEW_FILEICON_H
#define SCN_TITLEMENUNEW_FILEICON_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class FileIcon {
public:
    FileIcon(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);

    void update(u32 file);
    void updateFrame();

private:
    lyt::Layout mLayout;
};

}}  // namespace scn::titlemenunew

#endif
