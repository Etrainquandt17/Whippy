#include "scn/step/item/CliffEdgeBoundCtrl.h"

#include "gobj/Move.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"

namespace scn {
namespace step {
namespace item {

CliffEdgeBoundCtrl::CliffEdgeBoundCtrl(Item& item, f32 speedH, f32 speedV)
    : mObj(item)
    , mSpeedH(speedH)
    , mSpeedV(speedV)
    , mInterval(0) {}

CliffEdgeBoundCtrl::~CliffEdgeBoundCtrl() {}

void CliffEdgeBoundCtrl::update() {
    if (mInterval != 0) {
        mInterval--;
    }
}

bool CliffEdgeBoundCtrl::chkBound() {
    if (mInterval != 0) {
        return false;
    }
    if (!mObj.mapColl().isOnCliffEdge()) {
        return false;
    }
    f32 sign = mObj.mapColl().isCliffEdgeRight() ? 1.0f : -1.0f;
    mObj.move().setSpeedH(mSpeedH * sign);
    mObj.move().setSpeedV(mSpeedV);
    mInterval = 60;
    return true;
}

}}}  // namespace scn::step::item
