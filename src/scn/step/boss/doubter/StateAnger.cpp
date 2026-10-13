#include "scn/step/boss/doubter/StateAnger.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/ColorF.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/info/BossPanel.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateAnger::StateAnger(Boss* boss) : StateBase(boss), mScale(1.0f), mIsScaling(false) {
    obj().footState().setGround();
    obj().invincible().setPermNoFlash();
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_6);
    obj().model().reqScript(0x1F);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().infoBossPanel().transformStart();
}

StateAnger::~StateAnger() {
    obj().infoBossPanel().transformEnd();
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_2);
    obj().flash().custom().setIsValid(false);
    obj().flash().attack().setEnd(hel::common::ColorF(1.0f, 1.0f, 1.0f, 1.0f).toGXColorAsNormal());
}

void StateAnger::procAnim() {
    const Param& param = obj().param().doubter();
    if (obj().scriptTrigger().get(0)) {
        mIsScaling = true;
    }
    if (mIsScaling) {
        mScale = hel::math::Math::LinearInterpolation(mScale, param.mScaleAnger, param.mAngerScaleRate);
        obj().model().setScale(hel::math::Vector3::ALL_ONE * mScale);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    hel::common::ColorF color(0.0f, 0.0f, 0.0f, 1.0f);
    if (obj().model().anim().frame() < 120.0f) {
        f32 rate = obj().model().anim().frame() / 120.0f;
        f32 power = 0.5f * hel::math::Math::SinDegF(90.0f * rate);
        color.set(power * (0.5f * (1.0f + hel::math::Math::SinDegF(720.0f * rate))),
                  power * (0.5f * (1.0f + hel::math::Math::SinDegF(720.0f * rate + 120.0f))),
                  power * (0.5f * (1.0f + hel::math::Math::SinDegF(720.0f * rate + 240.0f))), 1.0f);
        obj().flash().custom().setOperation(static_cast<g3d::ColorAnimFlashOp>(1));
    } else {
        // TODO: totalFrame() is unsigned in the original.
        f32 rate = (obj().model().anim().frame() - 120.0f) / static_cast<u32>(obj().model().anim().totalFrame() - 120);
        color.set(1.0f, 1.0f, 1.0f, hel::math::Math::SinDegF(90.0f * (1.0f - rate)));
        obj().flash().custom().setOperation(static_cast<g3d::ColorAnimFlashOp>(0));
    }
    obj().flash().custom().setIsValid(true);
    obj().flash().custom().setColor(color.toGXColorAsNormal());
}

void StateAnger::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateAnger::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
