#ifndef SCN_TITLEMENUNEW_THEARENA_H
#define SCN_TITLEMENUNEW_THEARENA_H

#include "lyt/Layout.h"
#include "scn/titlemenunew/ClearMark.h"
#include "scn/titlemenunew/IModeButton.h"
#include "types.h"

namespace info {
class AnimSyncer;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class TheArena : public IModeButton {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
        KIND_2,
    };

    TheArena(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind, info::AnimSyncer& animSyncer);

    void updateFrame();
    void updateClearMark();
    void show();
    void hide();
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
    Kind mKind;
    lyt::Layout mLayout;
    ClearMark mClearMark;
};

}
}

#endif
