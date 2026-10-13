#ifndef SCN_STEP_GIMMICK_SWITCHRECEIVERMANAGER_H
#define SCN_STEP_GIMMICK_SWITCHRECEIVERMANAGER_H

#include "types.h"

namespace scn {
namespace step {
namespace gimmick {

class SwitchReceiverManager {
public:
    void onSwitchOn(u32 id);
    void onSwitchOff(u32 id);
    void onSwitchToggle(u32 id);
};

}}}  // namespace scn::step::gimmick

#endif
