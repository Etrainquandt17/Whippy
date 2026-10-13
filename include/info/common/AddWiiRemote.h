#ifndef INFO_COMMON_ADDWIIREMOTE_H
#define INFO_COMMON_ADDWIIREMOTE_H

#include "lyt/Layout.h"
#include "types.h"

namespace info {
namespace common {

class AddWiiRemote {
public:
    class Remote {
    public:
        bool isConnected() const;
        void phaseOn();

    private:
        u8 _0[0x90];
        lyt::Layout _90;
        lyt::Layout _220;
        lyt::Layout _3B0;
        lyt::Layout _540;
        int mPhase;
    };
};

}
}

#endif
