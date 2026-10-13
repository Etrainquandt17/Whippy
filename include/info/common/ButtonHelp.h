#ifndef INFO_COMMON_BUTTONHELP_H
#define INFO_COMMON_BUTTONHELP_H

#include "info/common/WiiButton.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace common {

class ButtonHelp {
public:
    ButtonHelp(mem::IAllocator& allocator, const lyt::PaneAccessor& pane, WiiButton::Kind kind);

    void blink();
    void push();
    bool isPushEnd() const;
    void updateFrame();
    void setText(const wchar_t* text);
    void waitNoShadow();
    void pushHold();

private:
    u8 _0[0x324];
};

}}  // namespace info::common

#endif
