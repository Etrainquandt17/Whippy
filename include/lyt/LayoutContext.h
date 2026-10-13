#ifndef LYT_LAYOUTCONTEXT_H
#define LYT_LAYOUTCONTEXT_H

#include "types.h"

namespace mem {
class IAllocator;
}

namespace lyt {

class LayoutContext {
public:
    LayoutContext(const char* path, const char* name, mem::IAllocator& allocator);

    static mem::IAllocator& DefaultAllocator();

private:
    u8 _0[0x64];
};

}

#endif
