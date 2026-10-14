#include "scn/step/enemy/waddledee/StateSmashedEnd.h"

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
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWalkAround.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "scn/step/enemy/waddledee/ParamData.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateSmashedEnd::StateSmashedEnd(Enemy* enemy) : StateBase(enemy), mFrame(obj().param().waddledee().mSmashedEndFrame) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    obj().objColl().bodyColl().setStateHitOnly();
    obj().model().rotCtrl().setRotVIntpRate(1.0f);
    obj().model().rotCtrl().setRotHIntpRate(1.0f);
    Vector3 pos = obj().location().pos() + Vector3(0.0f, 0.3f, 0.0f);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x9F), pos);
}

StateSmashedEnd::~StateSmashedEnd() {
    obj().objColl().bodyColl().setStateNormal();
    obj().model().rotCtrl().resetRotIntpRate();
}

void StateSmashedEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
    if (mFrame == 0) {
        obj().move().setSpeedH(0.0f);
        obj().move().setSpeedV(0.0f);
        if (obj().variation() == 3) {
            obj().stateChanger().setNextState<common::StateWalkAround, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(objPtr());
        }
    } else {
        mFrame--;
    }
}

void StateSmashedEnd::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::waddledee
