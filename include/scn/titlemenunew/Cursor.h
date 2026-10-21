#ifndef SCN_TITLEMENUNEW_CURSOR_H
#define SCN_TITLEMENUNEW_CURSOR_H

#include "scn/titlemenunew/FileKind.h"
#include "scn/titlemenunew/ModeKind.h"
#include "types.h"

namespace lyt {
class PaneAccessor;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class Cursor {
public:
    Cursor(mem::IAllocator& allocator);
    ~Cursor();

    void frontPane(const lyt::PaneAccessor& pane);
    void show();
    void hide();
    void focus();
    void select(ModeKind kind);
    FileKind selectedFile() const;
    ModeKind selectedMode() const;

private:
    u32 _0[0xC7];
};

}}  // namespace scn::titlemenunew

#endif
