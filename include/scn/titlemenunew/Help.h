#ifndef SCN_TITLEMENUNEW_HELP_H
#define SCN_TITLEMENUNEW_HELP_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "scn/titlemenunew/IModeButton.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class Help : public IModeButton {
public:
    Help(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);

    void updateFrame();

    virtual lyt::PaneAccessor parent();
    virtual void setParent(const lyt::PaneAccessor& parent);
    virtual lyt::PaneAccessor cursorParent();
    virtual void focus();
    virtual void unfocus();
    virtual void decide();
    virtual void unlock();
    virtual bool isAnimEnd() const;

private:
    lyt::Layout mLayout;
};

}
}

#endif
