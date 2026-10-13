#include "scn/step/enemy/pierce/StateFlyWait.h"

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
#include "scn/step/enemy/pierce/Custom.h"
#include "scn/step/enemy/pierce/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

StateFlyWait::StateFlyWait(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsAttack(false) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    Utility::TurnHero(obj());
}

StateFlyWait::~StateFlyWait() {}

void StateFlyWait::procAnim() {
    const ParamData& param = obj().param().pierce();
    bool isInArea = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInAimArea();
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (isInArea && index == 0) {
        if (!mIsAttack || ++mFrame == param.mAttackWaitFrame) {
            if (obj().target().isRightDir()) {
                obj().model().reqScript(11);
            } else {
                obj().model().reqScript(10);
            }
            mIsAttack = true;
        }
    } else if (!isInArea) {
        mFrame = 0;
        mIsAttack = false;
    }
    if ((index == 6 || index == 7) && obj().model().isAllEnd()) {
        obj().model().reqScript(0);
        mFrame = 0;
    }
}

void StateFlyWait::procMove() {
    const ParamData& param = obj().param().pierce();
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).turnHeroWithTime(param.mTurnFrame);
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

}}}}  // namespace scn::step::enemy::pierce
