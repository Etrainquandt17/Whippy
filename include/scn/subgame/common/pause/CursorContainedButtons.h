#ifndef SCN_SUBGAME_COMMON_PAUSE_CURSORCONTAINEDBUTTONS_H
#define SCN_SUBGAME_COMMON_PAUSE_CURSORCONTAINEDBUTTONS_H

#include "hel/common/MutableArray.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {

namespace boxmenu {
class SelectableBox;
}

namespace pause {

class CursorContainedButtons {
public:
    CursorContainedButtons() : mBoxes() {}

    void addBoxMenu(boxmenu::SelectableBox& box);

private:
    hel::common::MutableArray<boxmenu::SelectableBox*, 4> mBoxes;
};

}}}}  // namespace scn::subgame::common::pause

#endif
