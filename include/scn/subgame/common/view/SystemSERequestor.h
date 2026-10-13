#ifndef SCN_SUBGAME_COMMON_VIEW_SYSTEMSEREQUESTOR_H
#define SCN_SUBGAME_COMMON_VIEW_SYSTEMSEREQUESTOR_H

#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace view {

// TODO: members; the size is what boxmenu::ClosableBox gives it.
class SystemSERequestor {
public:
    SystemSERequestor();
    ~SystemSERequestor();

    void start(unsigned long label);
    void stop();

private:
    u32 _0[0x74 / 4];
};

}
}
}
}

#endif
