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

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateBack::StateBack(Enemy* enemy) : StateBase(enemy), mFrame(0), mTotalFrame(0), mDist(0.0f) {
    Vector2 diff = obj().location().pos().getXY();
    diff -= DynamicCastToRef<Custom, ICustom>(obj().custom()).initPos();
    mDist = diff.length();
    mFrame = mTotalFrame = static_cast<int>(mDist / obj().param().pacto().mBackSpeed);
}

void StateBack::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame > 0) {
        f32 rot = Utility::GetRotByDirType(obj());
        Vector2 dir(Math::SinDegF(rot), Math::CosDegF(rot));
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

}}}}  // namespace scn::step::enemy::pacto
