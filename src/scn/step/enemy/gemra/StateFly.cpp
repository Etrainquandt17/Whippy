#include "scn/step/enemy/gemra/StateFly.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/gemra/Custom.h"
#include "scn/step/enemy/gemra/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mWaitFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    mWaitFrame = obj().param().gemra().mFlyWaitFrame;
}

StateFly::~StateFly() {}

void StateFly::procAnim() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).updateDir();
    if (mWaitFrame == 0) {
        obj().brainCtrl().toValid();
    } else {
        mWaitFrame--;
    }
}

void StateFly::procMove() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).updatePos();
}

void StateFly::procFixPos() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).updateFixPos();
}

}
}
}
}
