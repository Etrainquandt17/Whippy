#ifndef SCN_WMAP_UNLOCKKINDUTIL_H
#define SCN_WMAP_UNLOCKKINDUTIL_H

#include "scn/step/LevelKind.h"
#include "scn/wmap/UnlockKind.h"

namespace scn {
namespace wmap {

class UnlockKindUtil {
public:
    static UnlockKind GetUnlockKindFromLevelKind(step::LevelKind kind);
};

}
}

#endif
