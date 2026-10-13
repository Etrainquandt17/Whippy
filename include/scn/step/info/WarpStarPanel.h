#ifndef SCN_STEP_INFO_WARPSTARPANEL_H
#define SCN_STEP_INFO_WARPSTARPANEL_H

#include "hel/math/Vector3.h"
#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {

class Component;

namespace info {

class WarpStarPanel {
public:
    WarpStarPanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Component& component);

    void updateFrame();
    void warpStarInit();
    void warpStarPosSet();
    void checkWarpStarPanelStart();
    void checkVisible();
    void checkDisappear();
    bool isNearWarpStar();
    void panelAppear();
    void panelDisappear();
    void constraintPos();

private:
    Component& mComponent;
    lyt::Layout mLayout;
    hel::math::Vector3 _194;
    bool _1A0;
    bool _1A1;
    bool _1A2;
    bool _1A3;
};

}}}  // namespace scn::step::info

#endif
