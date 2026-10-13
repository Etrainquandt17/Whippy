#ifndef PAUSE_COMPONENT_H
#define PAUSE_COMPONENT_H

#include "pause/ContextInit.h"
#include "pause/ContextOpen.h"
#include "types.h"

namespace lyt {
class Layout;
}

namespace mem {
class IAllocator;
}

namespace snd {
class SystemSERequestor;
}

namespace pause {

class FramePanel;
class HID;
class ResultSetter;

class Component {
public:
    ContextInit contextInit() const;
    ContextOpen contextOpen() const;
    mem::IAllocator& allocator();
    HID& hid();
    ResultSetter& resultSetter() const;
    snd::SystemSERequestor& seReq();
    lyt::Layout& base() const;
    FramePanel& framePanel();
    bool isReqClose() const;

private:
    ContextInit mContextInit;
};

}  // namespace pause

#endif
