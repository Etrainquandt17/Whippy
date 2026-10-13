#ifndef SCN_STEP_INFO_MANAGER_H
#define SCN_STEP_INFO_MANAGER_H

namespace info {
namespace complete {
class Manager;
}
}

namespace scn {
namespace step {
namespace info {

class InfoControl;
namespace challenge {
class Challenge;
}
class InfoGameStatus;
namespace lvmap {
class LvMap;
}

class Manager {
public:
    InfoGameStatus& gameStatus();
    InfoControl& infoControl();
    lvmap::LvMap& lvMap();
    bool isInfoControl();
    ::info::complete::Manager& completeManager();
    challenge::Challenge& challenge();
};

}
}
}

#endif
