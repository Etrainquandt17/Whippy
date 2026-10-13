#ifndef HID_RUMBLEREQUESTOR_H
#define HID_RUMBLEREQUESTOR_H

#include "types.h"

namespace hid {

class RumbleManager;

class RumbleRequestor {
public:
    RumbleRequestor(RumbleManager& manager, u32 index);
    ~RumbleRequestor();

    void start(u32 kind);
    void stop();
    u32 padChan() const;
    void update();
    bool isPause() const;
    void pauseInc();
    void pauseDec();
    void pauseReset();

private:
    u32 _0[6];
};

}

#endif
