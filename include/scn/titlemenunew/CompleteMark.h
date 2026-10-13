#ifndef SCN_TITLEMENUNEW_COMPLETEMARK_H
#define SCN_TITLEMENUNEW_COMPLETEMARK_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace info {
class AnimSyncer;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class CompleteMark {
public:
    CompleteMark(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, info::AnimSyncer& animSyncer);

    void show();
    void hide();
    void select();
    void deselect();
    void updateFrame();

private:
    lyt::Layout mLayout;
    u32 _190;
};

}
}

#endif
