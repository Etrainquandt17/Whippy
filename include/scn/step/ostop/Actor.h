#ifndef SCN_STEP_OSTOP_ACTOR_H
#define SCN_STEP_OSTOP_ACTOR_H

#include "scn/step/ostop/Flag.h"
#include "types.h"

namespace ostop {

class IActorEventReceiver;

}

namespace scn {
namespace step {
namespace ostop {

class Manager;

// TODO: members.
class Actor {
public:
    Actor(Manager& manager, Flag flag);
    ~Actor();

    void registerEventReceiver(::ostop::IActorEventReceiver& receiver);
    void unregisterEventReceiver(::ostop::IActorEventReceiver& receiver);
    bool isStopped() const;
    bool isStoppedNormal() const;
    bool isNotStopped() const;
    bool isSpecial() const;
    void setIsSpecial(bool isSpecial);
    u32 groupBitFlag() const;

private:
    u32 _0[4];
};

}}}  // namespace scn::step::ostop

#endif
