#include "scn/step/item/SuperStop.h"

#include "scn/step/Component.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/ObjStop.h"
#include "scn/step/spstop/Manager.h"

namespace scn {
namespace step {
namespace item {

SuperStop::SuperStop(Item& item)
    : mObj(item)
    , mIsBornInStop(item.comp().superStopManager().isStopped())
    , mIsSpecial(false) {
    mObj.comp().superStopManager().registerEventReceiver(*this);
}

SuperStop::~SuperStop() {
    mObj.comp().superStopManager().unregisterEventReceiver(*this);
}

void SuperStop::onSuperStopStarted(const spstop::Manager&) {
    mIsSpecial = false;
    if (mIsBornInStop) {
        mObj.objStop().setSpecial();
        mIsBornInStop = false;
        mIsSpecial = true;
    }
}

void SuperStop::onSuperStopFinished(const spstop::Manager&) {
    if (mIsSpecial) {
        mObj.objStop().unsetSpecial();
        mIsSpecial = false;
    }
}

}}}  // namespace scn::step::item
