#ifndef SCN_STEP_ENEMY_SUPERSTOP_H
#define SCN_STEP_ENEMY_SUPERSTOP_H

#include "scn/step/spstop/IEventReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

class SuperStop : public spstop::IEventReceiver {
public:
    SuperStop(Enemy& enemy);
    virtual ~SuperStop();
    virtual void onSuperStopStarted(const spstop::Manager& manager);
    virtual void onSuperStopFinished(const spstop::Manager& manager);

    void onObjCollReactHit();

private:
    Enemy& mObj;
    bool mIsSpecial;
};

}
}
}

#endif
