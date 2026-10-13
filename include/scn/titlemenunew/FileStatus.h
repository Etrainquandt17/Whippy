#ifndef SCN_TITLEMENUNEW_FILESTATUS_H
#define SCN_TITLEMENUNEW_FILESTATUS_H

#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "mem/ExplicitAutoDeleteArray.h"
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

class FileStatus : public IModeButton {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
        KIND_2,
    };

    FileStatus(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, bool, Kind kind, u32 file, info::AnimSyncer& animSyncer);

    void updateFrame();
    void hide();
    void show();
    void updateStatus(u32 file);
    void select();
    void deselect();

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
    mem::ExplicitAutoDeleteArray<lyt::Layout, 5> _194;
    ClearMark mClearMark;
    u32 _344;
    bool _348;
};

}}  // namespace scn::titlemenunew

#endif
