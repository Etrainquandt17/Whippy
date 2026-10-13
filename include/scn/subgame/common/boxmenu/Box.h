#ifndef SCN_SUBGAME_COMMON_BOXMENU_BOX_H
#define SCN_SUBGAME_COMMON_BOXMENU_BOX_H

#include "lyt/Layout.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace subgame {
namespace common {
namespace boxmenu {

class Box {
public:
    Box();
    Box(lyt::Layout& layout);

    bool isEmpty() const;
    lyt::PaneAccessor rootPane();
    lyt::PaneAccessor pane(const char* name);
    void setAnimByName(const char* name);
    void setFrameToHead();
    void setFrameToTail();
    void setFrameRate(f32 rate);
    void start(bool doLoop);
    bool isAnimEnd() const;

private:
    util::ObjRefHandle<lyt::Layout> mLayout;
};

}}}}  // namespace scn::subgame::common::boxmenu

#endif
