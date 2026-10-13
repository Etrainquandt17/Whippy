#include "scn/step/enemy/liepa/StateMoveAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/liepa/ParamData.h"
#include "scn/step/hero/Manager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

StateMoveAttack::StateMoveAttack(Enemy* enemy, Config config)
    : StateBase(enemy), mFrame(0), mTotalFrame(0), mShotFrame(0), mVelocity(hel::math::Vector3::ZERO), mIsMove(false),
      mConfig(config) {
    obj().model().reqScript(4);
    obj().move().resetVelocity();
}

StateMoveAttack::~StateMoveAttack() {}

void StateMoveAttack::procAnim() {
    const ParamData& param = obj().param().liepa();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mTotalFrame++;
    if (!mIsMove) {
        if (mTotalFrame < param.mMoveWaitFrame) {
            if (mTotalFrame % 5 == 0) {
                obj().model().shake().request(static_cast<chara::ShakeKind>(1));
            }
        } else if (custom.isExistHeroInAttackRange()) {
            mIsMove = true;
            mVelocity = obj().comp().heroManager().getNearestPlayerPos(obj().location().pos()) - obj().location().pos();
            if (!mVelocity.isZeroLoose(0.00001f)) {
                mVelocity.normalize();
            } else {
                mVelocity = -hel::math::Vector3::BASIS_X;
            }
            mVelocity *= mConfig._0;
        }
    } else if (obj().model().getCurrentScriptIndex() == 7) {
        mShotFrame++;
        if (mShotFrame == param.mShotFrame) {
            custom.reqShot();
        }
        if (obj().model().anim().isAnimEnd()) {
            obj().model().reqScript(4);
        }
    } else {
        mShotFrame = 0;
        mFrame++;
        if (!Utility::IsCameraOut(obj()) && custom.isExistHeroInAttackRange() && mFrame == param.mMoveAttackFrame) {
            mFrame = 0;
            obj().model().reqScript(7);
        }
    }
}

void StateMoveAttack::procMove() {
    hel::math::Vector3 pos = obj().location().pos();
    if (obj().model().getCurrentScriptIndex() != 7 || mFrame != 0) {
        pos += mVelocity;
    }
    obj().location().setPos(pos);
}

void StateMoveAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::liepa
