#include "scn/step/boss/roah/StateTacklePursuit.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/sfx/ScreenFade.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateTacklePursuit::StateTacklePursuit(Boss* boss, Config config, StateTackle::Config tackleConfig)
    : StateBase(boss), mFadeEndCount(0), mCount(0), mConfig(config), mTackleConfig(tackleConfig) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(21);
    f32 x = obj().location().pos().x;
    if (obj().comp().mainCamera().getCenter().x < x) {
        custom.mahoroaCtrl().getCustom().reqMotionWarpIn();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(2));
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE);
    obj().guard().setType(GUARD_TYPE_6);
#ifdef VERSION_SUKK01
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x635), 0);
#else
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x634), 0);
#endif
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4C2), 1);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x4CC), obj().location().pos());
    obj().soundSE().normal().start(0x45E);
    obj().soundSE().loop().start(0x45F);
    obj().comp().screenFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x64 });
    obj().comp().screenFade().setFadeIn(40);
    Utility::ControlHateOnAction(obj());
}

StateTacklePursuit::~StateTacklePursuit() {}

void StateTacklePursuit::procAnim() {
    mCount++;
    if (mCount % 5 == 0) {
        if (mFadeEndCount != 0) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(2));
        } else {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
        }
    }
    if (obj().comp().screenFade().isEnd()) {
        mFadeEndCount++;
    }
    if (mFadeEndCount == mConfig._0) {
        obj().stateChanger().setNextState<StateTackle, Boss*, StateTackle::Config>(objPtr(), mTackleConfig);
    }
}

void StateTacklePursuit::procMove() {
    const Param& param = obj().param().roah();
    f32 heroY = Utility::GetHatedHeroPos(obj()).y;
    f32 diff = heroY - obj().location().pos().y;
    if (obj().comp().screenFade().isEnd() && Math::Abs(diff) > param.mPursuitMargin) {
        bool isUp = heroY > obj().location().pos().y;
        Vector3 dir = Vector3::BASIS_Y * (isUp ? 1.0f : -1.0f);
        obj().move().accel(dir, mConfig._4);
    } else {
        obj().move().decel(gobj::MoveParamDecel::Create(mConfig._4._8));
    }
}

void StateTacklePursuit::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
