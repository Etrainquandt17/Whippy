#ifndef G3D_AUTOREQANIMREQINFO_H
#define G3D_AUTOREQANIMREQINFO_H

#include "hel/common/FixedString.h"
#include "types.h"

namespace g3d {

class AutoReqAnimReqInfo {
public:
    AutoReqAnimReqInfo();

    hel::common::FixedString<40> _0;
    hel::common::FixedString<40> _28;
    hel::common::FixedString<40> _50;
    bool _78;
    bool _79;
    bool _7A;
};

}  // namespace g3d

#endif
