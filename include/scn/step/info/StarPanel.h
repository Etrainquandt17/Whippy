#ifndef SCN_STEP_INFO_STARPANEL_H
#define SCN_STEP_INFO_STARPANEL_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {
namespace info {

class StarPanel {
public:
    StarPanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);

private:
    lyt::Layout mLayout;
    u32 _190[5];
};

}}}  // namespace scn::step::info

#endif
