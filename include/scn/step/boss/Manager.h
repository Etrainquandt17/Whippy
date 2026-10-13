#ifndef SCN_STEP_BOSS_MANAGER_H
#define SCN_STEP_BOSS_MANAGER_H

#include "scn/step/map/BinBossKind.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {

class ArenaCtrl;
class Boss;
class Desc;
class EnergySphereCtrl;
class LowperWindCtrl;

// TODO: members and the other functions.
class Manager {
public:
    util::ObjRefHandle<Boss> request(const Desc& desc);
    ArenaCtrl& arenaCtrl();
    LowperWindCtrl& lowperWindCtrl();
    EnergySphereCtrl& energySphereCtrl();
    u32 getBossCount() const;
    util::ObjRefHandle<Boss> getBossByIndex(u32 index);
    void setRetryBossKind(map::BinBossKind kind);
    u32 getRetryBossCount(map::BinBossKind kind);
    bool isBannedBossKind(map::BinBossKind kind);
};

}
}
}

#endif
