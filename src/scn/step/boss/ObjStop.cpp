#include "scn/step/boss/ObjStop.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {

ObjStop::ObjStop(Boss& boss) : mBoss(boss), mActor(boss.comp().objStopManager(), static_cast<ostop::Flag>(8)) {
    mActor.registerEventReceiver(*this);
}

ObjStop::~ObjStop() {
    mActor.unregisterEventReceiver(*this);
}

bool ObjStop::isStopped() const {
    return mActor.isStopped();
}

void ObjStop::setSpecial() {
    mActor.setIsSpecial(true);
}

void ObjStop::unsetSpecial() {
    mActor.setIsSpecial(false);
}

void ObjStop::onStopNormalStarted(const ::ostop::Actor& actor) {
    onStopPowerfulStarted(actor);
    mBoss.soundSE().onObjStopStarted();
}

void ObjStop::onStopNormalFinished(const ::ostop::Actor& actor) {
    mBoss.soundSE().onObjStopFinished();
    onStopPowerfulFinished(actor);
}

void ObjStop::onStopPowerfulStarted(const ::ostop::Actor& actor) {
    mBoss.effect().onObjStopStarted();
    mBoss.gearManager().onObjStopStarted();
    mBoss.model().onObjStopStarted();
    mBoss.custom()->onObjStopStarted();
}

void ObjStop::onStopPowerfulFinished(const ::ostop::Actor& actor) {
    mBoss.custom()->onObjStopFinished();
    mBoss.model().onObjStopFinished();
    mBoss.gearManager().onObjStopFinished();
    mBoss.effect().onObjStopFinished();
}

}}}  // namespace scn::step::boss
