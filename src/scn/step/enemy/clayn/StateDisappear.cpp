#include "scn/step/enemy/clayn/StateDisappear.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/clayn/Custom.h"
#include "scn/step/enemy/clayn/ParamData.h"
#include "scn/step/enemy/clayn/StateHideWait.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

StateDisappear::StateDisappear(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    obj().objColl().bodyColl().setStateNormal();
    obj().vacuumReceiver().setIsValid(true);
    obj().captureReceiver().setCanCapture(true);
    obj().soundSE().start(0x2eb);
}

StateDisappear::~StateDisappear() {
    obj().soundSE().stop();
}

void StateDisappear::procAnim() {
    const ParamData& param = obj().param().clayn();
    mFrame++;
    if (mFrame == param.mDisappearCollFrame) {
        obj().objColl().bodyColl().setStateXlu();
    }
    if (mFrame == param.mDisappearReceiverFrame) {
        obj().vacuumReceiver().setIsValid(false);
        obj().captureReceiver().setCanCapture(false);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateHideWait, Enemy*>(objPtr());
    }
}

void StateDisappear::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setPos();
}

void StateDisappear::procFixPos() {}

}}}}  // namespace scn::step::enemy::clayn
