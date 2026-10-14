#include "scn/step/enemy/clayn/StateAppear.h"

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
#include "scn/step/enemy/clayn/StateWait.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().captureReceiver().setCanCapture(false);
    obj().model().reqScript(8);
    obj().soundSE().start(0x2ea);
}

StateAppear::~StateAppear() {
    obj().soundSE().stop();
}

void StateAppear::procAnim() {
    const ParamData& param = obj().param().clayn();
    mFrame++;
    if (mFrame >= param.mAppearCollFrame) {
        obj().objColl().bodyColl().setStateNormal();
    }
    if (mFrame >= param.mAppearReceiverFrame) {
        obj().vacuumReceiver().setIsValid(true);
        obj().captureReceiver().setCanCapture(true);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateAppear::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setPos();
}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::clayn
