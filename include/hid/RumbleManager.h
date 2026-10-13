#ifndef HID_RUMBLEMANAGER_H
#define HID_RUMBLEMANAGER_H

#include "hid/RumbleResource.h"
#include "types.h"

namespace hid {

class RumbleRequestor;

class RumbleManager {
public:
    RumbleManager(RumbleResourceKind kind);
    ~RumbleManager();

    void update();
    void pause();
    void unpause();
    void stopAll();
    void addRequestor(RumbleRequestor& requestor);
    void removeRequestor(RumbleRequestor& requestor);

private:
    // TODO: names and types. The size is what scn::subgame::common::rumble::Manager allocates.
    u32 _0[0x14];
};

}  // namespace hid

#endif
