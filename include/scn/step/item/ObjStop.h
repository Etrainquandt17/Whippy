#ifndef SCN_STEP_ITEM_OBJSTOP_H
#define SCN_STEP_ITEM_OBJSTOP_H

#include "ostop/IActorEventReceiver.h"
#include "scn/step/ostop/Actor.h"

namespace scn {
namespace step {
namespace item {

class Item;

class ObjStop : public ::ostop::IActorEventReceiver {
public:
    ObjStop(Item& item);
    virtual ~ObjStop();
    virtual void onStopNormalStarted(const ::ostop::Actor& actor);
    virtual void onStopNormalFinished(const ::ostop::Actor& actor);
    virtual void onStopPowerfulStarted(const ::ostop::Actor& actor);
    virtual void onStopPowerfulFinished(const ::ostop::Actor& actor);

    u32 groupBitFlag() const;
    bool isStopped() const;
    bool isNotStopped() const;
    bool isSpecial() const;
    void setSpecial();
    void unsetSpecial();
    ostop::Actor& actor();

private:
    Item& mObj;
    ostop::Actor mActor;
};

}}}  // namespace scn::step::item

#endif
