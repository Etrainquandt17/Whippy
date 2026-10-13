#ifndef SCN_STEP_BOSS_SUPERSTOP_H
#define SCN_STEP_BOSS_SUPERSTOP_H

#include "scn/step/spstop/IEventReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class SuperStop : public spstop::IEventReceiver {
public:
    SuperStop(Boss& boss);
    virtual ~SuperStop();
    virtual void onSuperStopStarted(const spstop::Manager& manager);
    virtual void onSuperStopFinished(const spstop::Manager& manager);

    void onObjCollReactHit();
    void setAutoSpecial();
    void unsetAutoSpecial();
    void setSpecial();
    void unsetSpecial();

private:
    Boss& mBoss;
    bool mIsSpecial;
    bool mIsStopped;
    bool mIsAutoSpecial;
};

}
}
}

#endif
