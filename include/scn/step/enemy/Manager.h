#ifndef SCN_STEP_ENEMY_MANAGER_H
#define SCN_STEP_ENEMY_MANAGER_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {

class Desc;
class Enemy;

// TODO: members and the other functions.
class Manager {
public:
    util::ObjRefHandle<Enemy> request(const Desc& desc);
    bool isExistSuperEnemy() const;
    void reqDeadAllEnemy();
    void reqDeadAllEnemyForBoss();
    void reqDeadAllEnemyForMBoss();
    void reqDeadAllEnemyWithNormalProcess();
    util::ObjRefHandle<Enemy> getEnemyByOCollOwnerUID(u64 uid);
    util::ObjRefHandle<Enemy> getEnemyByID(u32 id);
};

}
}
}

#endif
