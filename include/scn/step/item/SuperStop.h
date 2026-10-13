#ifndef SCN_STEP_ITEM_SUPERSTOP_H
#define SCN_STEP_ITEM_SUPERSTOP_H

#include "scn/step/spstop/IEventReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

class Item;

class SuperStop : public spstop::IEventReceiver {
public:
    SuperStop(Item& item);
    virtual ~SuperStop();
    virtual void onSuperStopStarted(const spstop::Manager& manager);
    virtual void onSuperStopFinished(const spstop::Manager& manager);

private:
    Item& mObj;
    bool mIsBornInStop;
    bool mIsSpecial;
};

}}}  // namespace scn::step::item

#endif
