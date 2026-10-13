#include "scn/step/enemy/barracu/StateEscape.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/barracu/ParamData.h"
#include "scn/step/enemy/barracu/StatePursuit.h"
#include "scn/step/enemy/barracu/StateSwimStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

StateEscape::StateEscape(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(12);
}

StateEscape::~StateEscape() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateEscape::procMove() {
    hel::math::Vector3 pos = obj().location().pos();
    pos.x += obj().target().getSign() * obj().param().barracu().mEscapeSpeed;
    obj().location().setPos(pos);
    if (++mFrame >= obj().param().barracu().mEscapeFrame) {
        if (obj().variation() == 0xa7) {
            obj().stateChanger().setNextState<StateSwimStraight, Enemy*>(objPtr());
        } else if (obj().variation() == 0xa8) {
            obj().stateChanger().setNextState<StatePursuit, Enemy*>(objPtr());
        }
    } else if (mFrame % 10 == 0) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
    }
}

}
}
}
}
