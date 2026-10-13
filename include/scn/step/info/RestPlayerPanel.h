#ifndef SCN_STEP_INFO_RESTPLAYERPANEL_H
#define SCN_STEP_INFO_RESTPLAYERPANEL_H

#include "info/sequence/Sequence.h"
#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {
namespace info {

class RestPlayerPanel {
public:
    RestPlayerPanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);

private:
    lyt::Layout mLayout;
    ::info::sequence::Sequence mSequence;
    u32 _2A0;
};

}}}  // namespace scn::step::info

#endif
