#ifndef SCN_STEP_BOSS_COMMON_STATEDEAD_H
#define SCN_STEP_BOSS_COMMON_STATEDEAD_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/map/BinItemKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss, int nodeKind);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void procAnimNormal();
    void procAnimSuper();
    void dead();
    void generateItem(map::BinItemKind kind);
};

}
}
}
}

#endif
