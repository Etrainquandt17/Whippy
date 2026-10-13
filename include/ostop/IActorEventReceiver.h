#ifndef OSTOP_IACTOREVENTRECEIVER_H
#define OSTOP_IACTOREVENTRECEIVER_H

namespace ostop {

class Actor;

class IActorEventReceiver {
public:
    virtual ~IActorEventReceiver();
    virtual void onStopNormalStarted(const Actor& actor) = 0;
    virtual void onStopNormalFinished(const Actor& actor) = 0;
    virtual void onStopPowerfulStarted(const Actor& actor) = 0;
    virtual void onStopPowerfulFinished(const Actor& actor) = 0;
};

}

#endif
