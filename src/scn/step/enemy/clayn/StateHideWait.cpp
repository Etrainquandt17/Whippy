#include "scn/step/enemy/clayn/StateHideWait.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/clayn/Custom.h"
#include "scn/step/enemy/clayn/ParamData.h"
#include "scn/step/enemy/clayn/StateAppear.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

StateHideWait::StateHideWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().captureReceiver().setCanCapture(false);
}

StateHideWait::~StateHideWait() {}

void StateHideWait::procAnim() {
    const ParamData& param = obj().param().clayn();
    switch (obj().variation()) {
    case 0x97:
        mFrame++;
        if (mFrame >= DynamicCastToRef<Custom, ICustom>(obj().custom()).getHideWaitCount()) {
            obj().stateChanger().setNextState<StateAppear, Enemy*>(objPtr());
        }
        break;
    case 0x98:
        if (Utility::IsHeroInRange(obj(), param.mRangeLeft, -param.mRangeRight, -param.mRangeV, param.mRangeV)) {
            obj().stateChanger().setNextState<StateAppear, Enemy*>(objPtr());
        }
        break;
    }
}

void StateHideWait::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setPos();
}

void StateHideWait::procFixPos() {}

}}}}  // namespace scn::step::enemy::clayn
