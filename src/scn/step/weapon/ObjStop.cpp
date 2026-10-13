#include "scn/step/weapon/ObjStop.h"

#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {

ObjStop::ObjStop(Weapon& weapon, ostop::Flag flag) : mObj(weapon), mActor(weapon.comp().objStopManager(), flag) {
    mActor.registerEventReceiver(*this);
}

ObjStop::~ObjStop() {
    mActor.unregisterEventReceiver(*this);
}

u32 ObjStop::groupBitFlag() const {
    return mActor.groupBitFlag();
}

bool ObjStop::isStopped() const {
    return mActor.isStopped();
}

bool ObjStop::isNotStopped() const {
    return mActor.isNotStopped();
}

bool ObjStop::isSpecial() const {
    return mActor.isSpecial();
}

void ObjStop::setSpecial() {
    mActor.setIsSpecial(true);
}

void ObjStop::unsetSpecial() {
    mActor.setIsSpecial(false);
}

ostop::Actor& ObjStop::actor() {
    return mActor;
}

void ObjStop::onStopNormalStarted(const ::ostop::Actor& actor) {
    onStopPowerfulStarted(actor);
    mObj.soundSE().pauseInc();
}

void ObjStop::onStopNormalFinished(const ::ostop::Actor& actor) {
    mObj.soundSE().pauseDec();
    onStopPowerfulFinished(actor);
}

void ObjStop::onStopPowerfulStarted(const ::ostop::Actor& actor) {
    mObj.effect().onObjStopStarted();
    mObj.model().onObjStopStarted();
    mObj.objColl().attack().setPause(true);
}

void ObjStop::onStopPowerfulFinished(const ::ostop::Actor& actor) {
    mObj.objColl().attack().setPause(false);
    mObj.model().onObjStopFinished();
    mObj.effect().onObjStopFinished();
}

}
}
}
