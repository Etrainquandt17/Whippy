#ifndef SCN_TITLEMENUNEW_FRAMES_H
#define SCN_TITLEMENUNEW_FRAMES_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class Frames {
public:
    Frames(mem::IAllocator& allocator);
    ~Frames();

    void updateFrame();
    lyt::PaneAccessor pane(const char* name);
    void fileSelect();
    void modeSelect();
    void setFileSelect();
    void setModeSelect();
    void back();
    bool isBackEnd() const;
    void updateMatrix();

private:
    lyt::Layout mLayout;
    u32 _190[0x239];
};

}}  // namespace scn::titlemenunew

#endif
