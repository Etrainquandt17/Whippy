#include "scn/step/enemy/clayn/StateFall.h"

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
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/common/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().objColl().bodyColl().setStateNormal();
    obj().vacuumReceiver().setIsValid(true);
    obj().captureReceiver().setCanCapture(true);
    obj().model().reqScript(1);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    if (obj().model().anim().currentG3DAnimIndex() == 2 && obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateFall::procMove() {
    if (obj().model().anim().currentG3DAnimIndex() == 1) {
        obj().move().airDecelFall(obj().param().common().mDecel, obj().param().common().mFall);
    }
}

void StateFall::procFixPos() {
    if (obj().model().anim().currentG3DAnimIndex() == 1) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().footState().setGround();
            obj().move().resetSpeedV();
            obj().model().reqScript(2);
        }
    } else if (!obj().mapColl().result().mIsHitFloor) {
        obj().footState().setAir();
        obj().model().reqScript(1);
    }
}

}
}
}
}
