#include "scn/step/enemy/bulby/StateHide.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/bulby/Custom.h"
#include "scn/step/enemy/bulby/ParamData.h"
#include "scn/step/enemy/bulby/StateWait.h"
#include "scn/step/enemy/common/StateFall.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

StateHide::StateHide(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
}

void StateHide::procAnim() {
    if (++mFrame == obj().param().bulby().mHideFrame) {
        if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isBuried()) {
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x124), 0);
            obj().soundSE().start(0x2e7);
        }
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateHide::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::bulby
