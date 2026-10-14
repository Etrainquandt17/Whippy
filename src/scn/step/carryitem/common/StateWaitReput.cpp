#include "scn/step/carryitem/common/StateWaitReput.h"

#include "gobj/Move.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/IndiviUtil.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/Utility.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/SoundSE.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

StateWaitReput::StateWaitReput(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFrame(0) {
    obj().effect().releaseAndVanish();
    obj().effectBack().releaseAndVanish();
    obj().effectWarp().releaseAndVanish();
    obj().move().resetVelocity();
    obj().setIsEnableCarry(false);
    obj().model().setVisibility(false);
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().setCanGather(false);
    if (IndiviUtil::HasShadow(obj().kind())) {
        obj().shadow().setVisibility(false);
    }
}

StateWaitReput::~StateWaitReput() {
    if (IndiviUtil::HasShadow(obj().kind())) {
        obj().shadow().setVisibility(true);
    }
    obj().setCanGather(true);
    obj().vacuumReceiver().setIsValid(true);
    obj().mapColl().setValid(true);
    obj().model().setVisibility(true);
    obj().setIsEnableCarry(true);
    obj().setReputStart(false);
}

void StateWaitReput::procAnim() {
    mFrame++;
    if (mFrame == obj().param().common()._80) {
        obj().setReputStart(true);
    }
    if (mFrame == obj().param().common()._84 && Utility::InScreen(obj(), 3.0f)) {
        obj().effect().requestP(static_cast<effect::Kind>(0xA9), obj().centerPos());
        obj().soundSE().start(0xF1);
    }
    if (mFrame >= obj().param().common()._88) {
        obj().reput();
    }
}

}}}}  // namespace scn::step::carryitem::common
