#ifndef SCN_TITLEMENUNEW_UNLOCKMESSAGE_H
#define SCN_TITLEMENUNEW_UNLOCKMESSAGE_H

#include "types.h"

namespace lyt {
class PaneAccessor;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class UnlockMessage {
public:
    UnlockMessage(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);
    ~UnlockMessage();

    void updateFrame();
    void open(const char* name);
    bool closed() const;

private:
    u32 _0[0xE9];
};

}}  // namespace scn::titlemenunew

#endif
