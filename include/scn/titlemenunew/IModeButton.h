#ifndef SCN_TITLEMENUNEW_IMODEBUTTON_H
#define SCN_TITLEMENUNEW_IMODEBUTTON_H

#include "lyt/PaneAccessor.h"
#include "types.h"

namespace scn {
namespace titlemenunew {

class IModeButton {
public:
    virtual lyt::PaneAccessor parent() = 0;
    virtual void setParent(const lyt::PaneAccessor& parent) = 0;
    virtual lyt::PaneAccessor cursorParent() = 0;
    virtual void focus() = 0;
    virtual void unfocus() = 0;
    virtual void decide() = 0;
    virtual void unlock() = 0;
    virtual bool isAnimEnd() const = 0;
};

}}  // namespace scn::titlemenunew

#endif
