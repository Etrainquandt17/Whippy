#ifndef SCN_STEP_BOSS_OBJSTOP_H
#define SCN_STEP_BOSS_OBJSTOP_H

#include "ostop/IActorEventReceiver.h"
#include "scn/step/ostop/Actor.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class ObjStop : public ::ostop::IActorEventReceiver {
public:
    ObjStop(Boss& boss);
    virtual ~ObjStop();
    virtual void onStopNormalStarted(const ::ostop::Actor& actor);
    virtual void onStopNormalFinished(const ::ostop::Actor& actor);
    virtual void onStopPowerfulStarted(const ::ostop::Actor& actor);
    virtual void onStopPowerfulFinished(const ::ostop::Actor& actor);

    bool isStopped() const;
    void setSpecial();
    void unsetSpecial();

private:
    Boss& mBoss;
    ostop::Actor mActor;
};

}}}  // namespace scn::step::boss

#endif
