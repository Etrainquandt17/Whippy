#include "scn/step/enemy/grandlowperbullet/StateHoming.h"

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
#include "scn/step/enemy/grandlowperbullet/ParamData.h"
#include "scn/step/enemy/grandlowperbullet/StateHomingHold.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

StateHoming::StateHoming(Enemy* enemy) : StateBase(enemy), mFrame(0), mXluFrame(3) {
    obj().footState().setAir();
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().model().reqScript(0);
}

StateHoming::~StateHoming() {
    if (mXluFrame != 0) {
        obj().objColl().setBodyCollStateNormal();
        obj().vacuumReceiver().setIsValid(true);
    }
}

void StateHoming::procAnim() {
    mFrame++;
    if (mXluFrame != 0 && --mXluFrame == 0) {
        obj().objColl().setBodyCollStateNormal();
        obj().vacuumReceiver().setIsValid(true);
    }
    if (mFrame == obj().param().grandlowperbullet().mHomingFrame) {
        obj().stateChanger().setNextState<StateHomingHold, Enemy*>(objPtr());
    }
}

void StateHoming::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateHoming::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().deadWithEffect();
    }
}

}
}
}
}
