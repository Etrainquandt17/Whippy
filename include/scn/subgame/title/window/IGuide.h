#ifndef SCN_SUBGAME_TITLE_WINDOW_IGUIDE_H
#define SCN_SUBGAME_TITLE_WINDOW_IGUIDE_H

#include "types.h"

namespace scn {
namespace subgame {

namespace common {
namespace boxmenu {
class SelectableBox;
}
namespace pause {
class CursorContainedButtons;
}
}

namespace title {
namespace window {

class IGuide {
public:
    // Pure but defined: the vtable's slot is zero in the original.
    virtual ~IGuide() = 0;
    virtual void start() {}
    virtual void reset() {}
    virtual bool up() { return false; }
    virtual bool down() { return false; }
    virtual bool left() { return false; }
    virtual bool right() { return false; }
    virtual bool enterA() { return false; }
    virtual bool enter2() { return false; }
    virtual bool back() { return false; }
    virtual bool select(const common::boxmenu::SelectableBox* box) { return false; }
    virtual bool unselect() { return false; }
    virtual void updateMain() {}
    virtual void updateDebug() {}
    virtual void draw() const {}
    virtual bool isEnd() const { return false; }
    virtual int nextSeq() const = 0;
    virtual const common::pause::CursorContainedButtons& buttons() const = 0;
    virtual bool isReturnable() const { return true; }
    virtual bool isReturnableAllPlayer() const { return false; }
    virtual bool isDisnableCursor() const { return false; }
    virtual bool isScreenCovered() const { return false; }
};

inline IGuide::~IGuide() {}

}
}
}
}

#endif
