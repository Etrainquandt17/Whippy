#ifndef SCN_STEP_ITEM_STATECALLBACK_H
#define SCN_STEP_ITEM_STATECALLBACK_H

#include "types.h"
#include "util/IStateCallback.h"

namespace scn {
namespace step {
namespace item {

class Item;

class StateCallback : public util::IStateCallback {
public:
    StateCallback(Item& item);
    virtual void onStateChanged(const util::IStateChanger& changer);

private:
    Item& mObj;
};

}}}  // namespace scn::step::item

#endif
