#include "scn/step/boss/whispy/StateShotAirBall.h"

#include "hel/math/Direction3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjList.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateShotAirBall::StateShotAirBall(Boss* boss, u32 count, u32 intervalFirst, u32 interval)
    : StateShotAirBallBase(boss, count, intervalFirst, interval), mTargetPos() {
    const Param& param = obj().param().whispy();
    mTargetPos = Utility::GetHatedHeroPos(obj()).getXY();
    mTargetPos.y += param.mAirBallTargetOffsetY;
}

void StateShotAirBall::reqAirBall() {
    const Param& param = obj().param().whispy();
    Vector2 pos = obj().location().pos().getXY();
    pos += param.mAirBallOffset;
    Vector2 speed = param.mAirBallSpeed;
    weapon::Desc desc(static_cast<weapon::Kind>(0xC), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    desc._24 = mTargetPos;
    obj().comp().weaponManager().request(desc);
    obj().soundSE().normal().start(0x320);
    Vector3 effectPos = obj().location().pos();
    effectPos += Vector3(param.mAirBallEffectOffset);
    obj().effect().normal().requestPD(static_cast<effect::Kind>(0x585), effectPos, Direction3::FRONT_TO_LEFT);
}

}}}}  // namespace scn::step::boss::whispy
