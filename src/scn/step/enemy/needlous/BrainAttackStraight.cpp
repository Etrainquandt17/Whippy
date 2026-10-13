#include "scn/step/enemy/needlous/BrainAttackStraight.h"

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
#include "scn/step/enemy/needlous/Custom.h"
#include "scn/step/enemy/needlous/ParamData.h"
#include "scn/step/enemy/needlous/StateWalkStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

BrainAttackStraight::BrainAttackStraight(Enemy& enemy) : BrainBase(enemy), mFrame(0) {}

bool BrainAttackStraight::onRecover() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).resetInitMoveCount();
    mfChangeWalkStraight();
    return true;
}

bool BrainAttackStraight::onLanding() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).resetInitMoveCount();
    mfChangeWalkStraight();
    return true;
}

void BrainAttackStraight::update() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isAttack()) {
        if (++mFrame >= obj().param().needlous().mAttackFrame) {
            mFrame = 0;
            custom.setAttack(false);
            custom.resetMoveCount(true);
            mfChangeWalkStraight();
        }
    } else {
        mFrame = 0;
    }
}

void BrainAttackStraight::mfChangeWalkStraight() {
    obj().objColl().clearBodyColl();
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    obj().objColl().addBodyColl(1, 0.28f * scale, hel::math::Vector2(0.3f * scale, 0.0f), hel::math::Vector2(-0.3f * scale, 0.0f));
    obj().stateChanger().setNextState<StateWalkStraight, Enemy*>(&obj());
}

}
}
}
}
