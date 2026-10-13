#ifndef SCN_STEP_CONTEXTBOSS_H
#define SCN_STEP_CONTEXTBOSS_H

#include "types.h"

namespace scn {
namespace step {

// TODO: members; the first 0x358 bytes of Context are one of these.
class ContextBoss {
public:
    u32 _0[0xD5];
    bool mIsShowLastBossAppearStagingEnf;
};

}
}

#endif
