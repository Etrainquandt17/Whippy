#include "scn/step/enemy/clayn/StateWait.h"

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
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/clayn/Custom.h"
#include "scn/step/enemy/clayn/ParamData.h"
#include "scn/step/enemy/clayn/StateDisappear.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().objColl().bodyColl().setStateNormal();
    obj().vacuumReceiver().setIsValid(true);
    obj().captureReceiver().setCanCapture(true);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    const ParamData& param = obj().param().clayn();
    switch (obj().variation()) {
    case 0x97:
        mFrame++;
        if (mFrame >= DynamicCastToRef<Custom, ICustom>(obj().custom()).getWaitCount()) {
            obj().stateChanger().setNextState<StateDisappear, Enemy*>(objPtr());
        }
        break;
    case 0x98:
        if (!Utility::IsHeroInRange(obj(), param.mRangeLeft, -param.mRangeRight, -param.mRangeV, param.mRangeV)) {
            obj().stateChanger().setNextState<StateDisappear, Enemy*>(objPtr());
        }
        break;
    }
}

void StateWait::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setPos();
}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::enemy::clayn
