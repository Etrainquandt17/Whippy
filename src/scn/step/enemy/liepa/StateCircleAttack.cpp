#include "scn/step/enemy/liepa/StateCircleAttack.h"

#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/liepa/ParamData.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

StateCircleAttack::StateCircleAttack(Enemy* enemy, Config config)
    : StateBase(enemy), mFrame(0), mShotFrame(0), mRadius(0.0f), mConfig(config) {
    obj().model().reqScript(4);
    mCenter = obj().location().pos().getXY();
}

StateCircleAttack::~StateCircleAttack() {}

void StateCircleAttack::procAnim() {
    const ParamData& param = obj().param().liepa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().getCurrentScriptIndex() == 7) {
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
        if (!Utility::IsCameraOut(obj()) && custom.isExistHeroInAttackRange() && mFrame % mConfig._0 == 0) {
            obj().model().reqScript(7);
        }
    }
}

void StateCircleAttack::procMove() {
    const ParamData& param = obj().param().liepa();
    mRadius = 0.95f * mRadius + 0.05f * param.mCircleRadius;
    f32 rate = static_cast<f32>(mFrame % param.mCircleFrame) / static_cast<f32>(param.mCircleFrame);
    Vector2 pos = mCenter;
    pos.x += mRadius * Math::SinDegF(360.0f * rate);
    pos.y += mRadius * Math::CosDegF(360.0f * rate);
    obj().location().setPos(pos.toVector3());
}

void StateCircleAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::liepa
