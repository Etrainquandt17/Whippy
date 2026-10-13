#ifndef FREEZE_FREEZEMANAGER_H
#define FREEZE_FREEZEMANAGER_H

#include "hel/common/ExplicitSingleton.h"
#include "types.h"

namespace freeze {

class FreezeManager : public hel::common::ExplicitSingleton<FreezeManager> {
public:
    FreezeManager(u8* xfb1, u8* xfb2);

private:
    u32 _0[4];
};

}  // namespace freeze

#endif
