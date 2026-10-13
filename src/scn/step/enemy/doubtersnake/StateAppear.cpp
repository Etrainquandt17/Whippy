#include "scn/step/enemy/doubtersnake/StateAppear.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
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
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/doubtersnake/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    f32 rate = obj().param().doubtersnake().mAppearFrameRate;
    obj().model().anim().setFrameRate(rate);
    obj().vacuumReceiver().setResistLevelStep(2);
    obj().objColl().bodyColl().setStateXlu();
}

StateAppear::~StateAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateAppear::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
    if (mFrame == obj().param().doubtersnake().mAppearCollFrame) {
        obj().objColl().bodyColl().setStateNormal();
        obj().vacuumReceiver().clearResistLevelStep();
    }
}

void StateAppear::procMove() {
    const ParamData& param = obj().param().doubtersnake();
    obj().move().airDecelFall(param.mAppearDecel, param.mAppearFall);
}

void StateAppear::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWall()) {
        obj().move().resetSpeedH();
        obj().target().invert();
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::doubtersnake
