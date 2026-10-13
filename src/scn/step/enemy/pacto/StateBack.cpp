#include "scn/step/enemy/pacto/StateBack.h"

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
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/pacto/ParamData.h"
#include "scn/step/enemy/pacto/StateEat.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateBack::StateBack(Enemy* enemy) : StateBase(enemy), mFrame(0), mTotalFrame(0), mDist(0.0f) {
    hel::math::Vector2 diff = obj().location().pos().getXY();
    diff -= hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).initPos();
    mDist = diff.length();
    mFrame = mTotalFrame = static_cast<int>(mDist / obj().param().pacto().mBackSpeed);
}

void StateBack::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame > 0) {
        f32 rot = Utility::GetRotByDirType(obj());
        hel::math::Vector2 dir(hel::math::Math::SinDegF(rot), hel::math::Math::CosDegF(rot));
        mFrame--;
        dir *= static_cast<f32>(mFrame) * mDist / static_cast<f32>(mTotalFrame);
        dir += custom.initPos();
        obj().location().setPos(dir.toVector3());
    } else if (custom.isCaptureHero()) {
        obj().stateChanger().setNextState<StateEat, Enemy*>(objPtr());
    } else {
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

}
}
}
}
