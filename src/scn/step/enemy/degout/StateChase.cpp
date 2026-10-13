#include "scn/step/enemy/degout/StateChase.h"

#include "app/Application.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Random.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/degout/Custom.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/degout/ParamData.h"
#include "scn/step/hero/Manager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

StateChase::StateChase(Enemy* enemy) : StateBase(enemy), mFrame(0), mAccel(), mSpeedMax(0.0f), mChaseFrame(0) {
    const degout::ParamData& param = obj().param().degout();
    obj().footState().setAir();
    obj().model().reqScript(7);
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector3 heroPos = Utility::GetNearestPlayerPos(obj()).toVector3();
    heroPos.y += param.mChaseTargetOffsetY;
    hel::math::Vector3 dir = heroPos - pos;
    if (dir.isZeroLoose(0.00001f)) {
        dir = hel::math::Vector3::ZERO;
    } else {
        dir.normalize();
    }
    switch (static_cast<u32>(obj().level())) {
    case 0:
        mAccel = dir * param.mChaseAccelLv0;
        mSpeedMax = param.mChaseSpeedMaxLv0;
        mChaseFrame = obj().param().degout().mChaseFrameLv0;
        break;
    case 1:
        mAccel = dir * param.mChaseAccelLv1;
        mSpeedMax = param.mChaseSpeedMaxLv1;
        mChaseFrame = obj().param().degout().mChaseFrameLv1;
        break;
    default:
        mAccel = dir * param.mChaseAccelLv2;
        mSpeedMax = param.mChaseSpeedMaxLv2;
        mChaseFrame = obj().param().degout().mChaseFrameLv2;
        break;
    }
    Utility::TurnHero(obj());
}

void StateChase::procAnim() {
    mFrame++;
    if (mFrame == mChaseFrame) {
        Utility::TurnHero(obj());
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    } else if (!Utility::IsPlayerExist(obj())) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

void StateChase::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const degout::ParamData& param = obj().param().degout();
    hel::math::Vector3 velocity = obj().move().velocity();
    if (!custom.isFirstChase() || mFrame >= param.mFirstChaseStartFrame) {
        hel::math::Vector3 accel = mAccel;
        if (Utility::ChkNururiByDir(obj(), 0.0f)) {
            velocity.x = mAccel.x = accel.x = 0.7f * obj().target().getSign();
            velocity.y = mAccel.y = accel.y = 0.7f;
        }
        velocity += accel;
        if (velocity.x > mSpeedMax) {
            velocity.x = mSpeedMax;
        } else if (velocity.x < -mSpeedMax) {
            velocity.x = -mSpeedMax;
        }
        if (velocity.y > mSpeedMax) {
            velocity.y = mSpeedMax;
        } else if (velocity.y < -mSpeedMax) {
            velocity.y = -mSpeedMax;
        }
        custom.setFirstChase(false);
        obj().move().setVelocity(velocity);
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
    } else if (mFrame >= param.mFirstChaseShakeFrame) {
        if (mFrame == param.mFirstChaseShakeFrame) {
            obj().soundSE().start(0x51f);
        }
        hel::math::Vector3 offset(0.0f, 0.0f, 0.0f);
        switch (static_cast<u32>(app::Application::Object().random().rand(5))) {
        case 0:
            offset.y += param.mFirstChaseShakeWidth;
            break;
        case 1:
            offset.x += param.mFirstChaseShakeWidth;
            break;
        case 2:
            offset.y -= param.mFirstChaseShakeWidth;
            break;
        case 3:
            offset.x -= param.mFirstChaseShakeWidth;
            break;
        }
        obj().model().setViewOffset(offset);
    }
}

}}}}  // namespace scn::step::enemy::degout
