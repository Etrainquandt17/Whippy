#include "scn/step/enemy/pacto/StateSpit.h"

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
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/pacto/ParamData.h"
#include "scn/step/enemy/pacto/StateBack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateSpit::StateSpit(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsAnimEnd(false) {
    obj().model().reqScript(10);
}

void StateSpit::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (++mFrame == 8) {
        custom.setDamageCaptureHero(obj().param().pacto().mEatDamage, true);
        if (custom.chkDeadHero()) {
            custom.releaseCaptureHero();
            return;
        }
        custom.vomitCaptureHero();
        obj().soundSE().start(0x50f);
    }
    if (!mIsAnimEnd && obj().model().isAllEnd()) {
        mIsAnimEnd = true;
        obj().model().reqScript(0);
    }
    if (mFrame == obj().param().pacto().mSpitEndFrame) {
        obj().stateChanger().setNextState<StateBack, Enemy*>(objPtr());
    }
}

}
}
}
}
