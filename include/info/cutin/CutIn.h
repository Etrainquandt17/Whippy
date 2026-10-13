#ifndef INFO_CUTIN_CUTIN_H
#define INFO_CUTIN_CUTIN_H

#include "lyt/Layout.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace cutin {

class CutIn {
public:
    CutIn(mem::IAllocator& allocator, const char*, const char*);

private:
    lyt::Layout mLayout;
};

}}  // namespace info::cutin

#endif
