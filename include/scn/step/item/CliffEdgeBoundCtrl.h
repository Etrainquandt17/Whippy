#ifndef SCN_STEP_ITEM_CLIFFEDGEBOUNDCTRL_H
#define SCN_STEP_ITEM_CLIFFEDGEBOUNDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace item {

class Item;

class CliffEdgeBoundCtrl {
public:
    CliffEdgeBoundCtrl(Item& item, f32 speedH, f32 speedV);
    ~CliffEdgeBoundCtrl();

    void update();
    bool chkBound();

private:
    Item& mObj;
    f32 mSpeedH;
    f32 mSpeedV;
    u32 mInterval;
};

}}}  // namespace scn::step::item

#endif
