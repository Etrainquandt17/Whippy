#ifndef SCN_ARENA_SELECT_SELECTPANEL_H
#define SCN_ARENA_SELECT_SELECTPANEL_H

#include "info/common/WiiButton.h"
#include "lyt/Layout.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace scn {
namespace arena {
namespace select {

class SelectSet;

class SelectPanel {
public:
    enum SelectPanelType {
        SELECT_PANEL_TYPE_0,
        SELECT_PANEL_TYPE_1,
    };

    SelectPanel(SelectSet& set, SelectPanelType type);
    ~SelectPanel();

    void updateFrame();
    void decide();
    void big();
    void small();

private:
    SelectSet& mSet;
    lyt::Layout mLayout;
    util::PlacementNew<lyt::Layout> mButton;
    util::PlacementNew< ::info::common::WiiButton> mWiiButton;
    SelectPanelType mType;
};

}}}  // namespace scn::arena::select

#endif
