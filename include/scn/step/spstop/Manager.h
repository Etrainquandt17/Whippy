#ifndef SCN_STEP_SPSTOP_MANAGER_H
#define SCN_STEP_SPSTOP_MANAGER_H

#include "hel/common/MutableArray.h"
#include "scn/step/spstop/IEventReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace spstop {

class Manager {
public:
    Manager();
    ~Manager();

    bool isStopped() const;
    void requestSuperStop();
    void unrequestSuperStop();
    void update();
    void registerEventReceiver(IEventReceiver& receiver);
    void unregisterEventReceiver(IEventReceiver& receiver);

private:
    hel::common::MutableArray<IEventReceiver*, 128> mReceivers;
    bool mIsRequested;
    bool mIsStopped;
};

}
}
}

#endif
