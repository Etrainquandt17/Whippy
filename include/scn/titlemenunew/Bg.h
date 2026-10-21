#ifndef SCN_TITLEMENUNEW_BG_H
#define SCN_TITLEMENUNEW_BG_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class Bg {
public:
    Bg(mem::IAllocator& allocator);
    ~Bg();

    void updateFrame();
    lyt::PaneAccessor pane(const char* name);
    void complete();
    void updateMatrix();

private:
    lyt::Layout mLayout;
    u32 _190[0x64];
};

}}  // namespace scn::titlemenunew

#endif
