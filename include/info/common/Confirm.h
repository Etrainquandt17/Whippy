#ifndef INFO_COMMON_CONFIRM_H
#define INFO_COMMON_CONFIRM_H

#include "info/common/Button.h"
#include "lyt/Layout.h"
#include "snd/SystemSERequestor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace common {

class Confirm {
public:
    Confirm(mem::IAllocator& allocator, const lyt::PaneAccessor& pane, const wchar_t* text1, const wchar_t* text2,
            const wchar_t* text3, const wchar_t* text4, bool flag1, bool flag2, const char* path, const char* name);

    void setText(const wchar_t* text);
    void setText0(const wchar_t* text);
    void setText1(const wchar_t* text);
    void changeButtonSizeSmall();
    void freezeOnYes(bool freeze);
    void freezeOnNo(bool freeze);
    void cancelFgm(u32 id);
    void closeFgm(u32 id);
    void defaultButton(u32 index);
    void open(u32 padChan);
    void forceClose();
    bool isClosed() const;
    // TODO: an enum; 0 is yes.
    int result() const;
    void updateFrame();

private:
    lyt::Layout _0;
    lyt::Layout _190;
    Button _320;
    Button _4BC;
    Button _658;
    u32 _7F4[0x7];
    snd::SystemSERequestor _810;
    u32 _884[0x3];
};

}
}

#endif
