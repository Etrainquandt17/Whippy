#include "scn/step/item/ObjStop.h"

#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/item/Item.h"

namespace scn {
namespace step {
namespace item {

ObjStop::ObjStop(Item& item)
    : mObj(item)
    , mActor(item.comp().objStopManager(), static_cast<ostop::Flag>(2)) {
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
    mObj.effectBack().requestPause();
    mObj.effect().requestPause();
    mObj.effectFore().requestPause();
    mObj.model().onObjStopStarted();
}

void ObjStop::onStopPowerfulFinished(const ::ostop::Actor& actor) {
    mObj.model().onObjStopFinished();
    mObj.effectBack().requestUnpause();
    mObj.effect().requestUnpause();
    mObj.effectFore().requestUnpause();
}

}}}  // namespace scn::step::item
