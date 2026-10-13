#ifndef SCN_MOVIE_LOADICON_H
#define SCN_MOVIE_LOADICON_H

#include "lyt/Layout.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace movie {

class LoadIcon {
public:
    LoadIcon(mem::IAllocator& allocator);

private:
    u32 _0;
    lyt::Layout _4;
    lyt::Layout _194;
    u32 _324[3];
};

}
}

#endif
