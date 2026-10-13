#ifndef SND_SYSTEMSEREQUESTOR_H
#define SND_SYSTEMSEREQUESTOR_H

#include "types.h"

namespace snd {

class SystemSERequestor {
public:
    SystemSERequestor();
    ~SystemSERequestor();

    void start(u32 id);

private:
    u8 _0[0x74];
};

}

#endif
