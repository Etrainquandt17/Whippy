#ifndef SCN_STEP_INFO_INFOCONTROL_H
#define SCN_STEP_INFO_INFOCONTROL_H

namespace scn {
namespace step {
namespace info {

class InfoControl {
public:
    bool isInfoVisible();
    void setIsPlayerOut(bool isOut);
};

}
}
}

#endif
