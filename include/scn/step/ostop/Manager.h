#ifndef SCN_STEP_OSTOP_MANAGER_H
#define SCN_STEP_OSTOP_MANAGER_H

#include "scn/step/ostop/Flag.h"
#include "types.h"

namespace scn {
namespace step {
namespace ostop {

class Manager {
public:
    bool isNotStopped(Flag flag) const;
    bool isStopped(Flag flag) const;
    bool canRequestStopNormal() const;
    void requestStopNormal(Flag flag);
    void requestStopPowerful(u32 frame);
};

}
}
}

#endif
