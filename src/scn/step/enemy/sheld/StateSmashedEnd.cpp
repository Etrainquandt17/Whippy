#include "scn/step/enemy/sheld/StateSmashedEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/sheld/ParamData.h"
#include "scn/step/enemy/sheld/StateEscape.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateSmashedEnd::StateSmashedEnd(Enemy* enemy) : StateBase(enemy), mWait(obj().param().sheld().mSmashedEndWait) {
    obj().footState().setGround();
    obj().model().reqScript(2);
    obj().objColl().bodyColl().setStateHitOnly();
    obj().model().rotCtrl().setRotVIntpRate(1.0f);
    obj().model().rotCtrl().setRotHIntpRate(1.0f);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x9f), obj().location().pos() + Vector3(0.0f, 0.3f, 0.0f));
}

StateSmashedEnd::~StateSmashedEnd() {
    obj().objColl().bodyColl().setStateNormal();
    obj().model().rotCtrl().resetRotIntpRate();
}

void StateSmashedEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
    if (mWait == 0) {
        obj().move().setSpeedH(0.0f);
        obj().move().setSpeedV(0.0f);
        obj().stateChanger().setNextState<StateEscape, Enemy*>(objPtr());
    } else {
        mWait--;
    }
}

}}}}  // namespace scn::step::enemy::sheld
