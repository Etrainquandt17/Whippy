#ifndef SCN_STEP_CARRYITEM_STATECALLBACK_H
#define SCN_STEP_CARRYITEM_STATECALLBACK_H

#include "types.h"
#include "util/IStateCallback.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class StateCallback : public util::IStateCallback {
public:
    StateCallback(CarryItem& carryItem);
    virtual void onStateChanged(const util::IStateChanger& changer);

private:
    CarryItem& mObj;
};

}}}  // namespace scn::step::carryitem

#endif
