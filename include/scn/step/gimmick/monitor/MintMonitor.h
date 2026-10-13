#ifndef SCN_STEP_GIMMICK_MONITOR_MINTMONITOR_H
#define SCN_STEP_GIMMICK_MONITOR_MINTMONITOR_H

namespace scn {
namespace step {
namespace gimmick {
namespace monitor {

class Monitor;

class MintMonitor {
public:
    static void Register(Monitor& obj);
    static void Unregister(Monitor& obj);
    static Monitor& Obj();
};

}
}
}
}

#endif
