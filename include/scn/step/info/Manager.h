#ifndef SCN_STEP_INFO_MANAGER_H
#define SCN_STEP_INFO_MANAGER_H

namespace scn {
namespace step {
namespace info {

class InfoControl;
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
};

}
}
}

#endif
