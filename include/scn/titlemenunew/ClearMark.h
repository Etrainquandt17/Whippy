#ifndef SCN_TITLEMENUNEW_CLEARMARK_H
#define SCN_TITLEMENUNEW_CLEARMARK_H

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

class ClearMark {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
        KIND_2,
        KIND_3,
    };

    ClearMark(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, info::AnimSyncer& animSyncer);

    void show(Kind kind);
    void select();
    void deselect();
    void hide();
    void updateFrame();

private:
    lyt::Layout mLayout;
    u32 _190;
};

}}  // namespace scn::titlemenunew

#endif
