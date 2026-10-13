#ifndef SCN_WMAP_UNLOCKMANAGER_H
#define SCN_WMAP_UNLOCKMANAGER_H

#include "scn/wmap/ItemKind.h"
#include "scn/wmap/UnlockKind.h"
#include "types.h"

namespace scn {
namespace wmap {

class Component;

class UnlockManager {
public:
    UnlockManager(Component& component);

    UnlockKind getAfterDemoUnlockKind() const;
    UnlockKind getUnlockKind() const;
    bool canMove(ItemKind kind) const;

private:
    u32 _0[5];
};

}
}

#endif
