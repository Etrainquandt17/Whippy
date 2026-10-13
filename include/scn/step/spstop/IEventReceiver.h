#ifndef SCN_STEP_SPSTOP_IEVENTRECEIVER_H
#define SCN_STEP_SPSTOP_IEVENTRECEIVER_H

namespace scn {
namespace step {
namespace spstop {

class Manager;

class IEventReceiver {
public:
    virtual ~IEventReceiver();
    virtual void onSuperStopStarted(const Manager& manager) = 0;
    virtual void onSuperStopFinished(const Manager& manager) = 0;
};

}
}
}

#endif
