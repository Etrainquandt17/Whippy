#ifndef SCN_TITLEMENUNEW_SUBGAME_H
#define SCN_TITLEMENUNEW_SUBGAME_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "scn/titlemenunew/IModeButton.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class SubGame : public IModeButton {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
    };

    SubGame(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind);

    void updateFrame();
    void enable(bool flag);

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

}}  // namespace scn::titlemenunew

#endif
