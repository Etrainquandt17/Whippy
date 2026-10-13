#ifndef SCN_SUBGAME_COMMON_UTIL_DPDMANAGER_H
#define SCN_SUBGAME_COMMON_UTIL_DPDMANAGER_H

#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace util {

class DpdManager {
public:
    DpdManager();
    virtual ~DpdManager();

    void inc();
    void dec();

private:
    u32 _4[2];
};

}
}
}
}

#endif
