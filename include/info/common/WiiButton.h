#ifndef INFO_COMMON_WIIBUTTON_H
#define INFO_COMMON_WIIBUTTON_H

#include "lyt/Layout.h"
#include "mem/IAllocator.h"
#include "types.h"

namespace info {
namespace common {

class WiiButton {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
        KIND_2,
        KIND_3,
        KIND_4,
    };

    WiiButton(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind);

    void hide();
    void appearWait();
    void appearWaitNoShadow();
    void appearBlink();
    void disappear();
    void wait();
    void waitNoShadow();
    void blink();
    void blink2();
    void push();
    void hold();
    void updateFrame();
    void setFrame(f32 frame);
    void changeDoLoop(bool doLoop);

private:
    lyt::Layout mLayout;
    bool _190;
    bool _191;
    // The class is 0x194 bytes where it is allocated (scn::wmap::info::LevelName); lyt::Layout has no alignment yet.
    u8 _192[2];
};

}}  // namespace info::common

#endif
