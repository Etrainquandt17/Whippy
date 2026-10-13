#ifndef SCN_STEP_BOSS_MANAGER_H
#define SCN_STEP_BOSS_MANAGER_H

#include "scn/step/hero/AbilityKind.h"
#include "scn/step/map/BinBossKind.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

class ContextBoss;

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
    ContextBoss context();
    void setShowLastBossAppearStagingEnf();
    void clearShowLastBossAppearStagingEnf();
    LowperWindCtrl& lowperWindCtrl();
    EnergySphereCtrl& energySphereCtrl();
    u32 getBossCount() const;
    u32 getCommanderCount() const;
    void requestCommander(const Desc& desc);
    util::ObjRefHandle<Boss> getBossByIndex(u32 index);
    void setRetryBossKind(map::BinBossKind kind);
    u32 getRetryBossCount(map::BinBossKind kind);
    bool isBannedBossKind(map::BinBossKind kind);
    util::ObjRefHandle<Boss> getBossByObjCollOwnerID(u64 id);
    util::ObjRefHandle<Boss> getBossByKind(map::BinBossKind kind);
    void setKeptAbility();
    void clearKeptAbility();
    u32 keptAbilityCount();
    hero::AbilityKind getKeptAbility(u32 index);
};

}}}  // namespace scn::step::boss

#endif
