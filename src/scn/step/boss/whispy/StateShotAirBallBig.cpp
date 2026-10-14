#include "scn/step/boss/whispy/StateShotAirBallBig.h"

#include "hel/math/Direction3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
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

StateShotAirBallBig::StateShotAirBallBig(Boss* boss, u32 count, u32 intervalFirst, u32 interval)
    : StateShotAirBallBase(boss, count, intervalFirst, interval) {}

void StateShotAirBallBig::reqAirBall() {
    const Param& param = obj().param().whispy();
    Vector2 pos = obj().location().pos().getXY();
    Vector2 offset = param.mAirBallBigOffset;
    pos += offset;
    reqAirBallIN(offset + param.mAirBallBigOffset0, pos + param.mAirBallBigTarget0);
    reqAirBallIN(offset + param.mAirBallBigOffset1, pos + param.mAirBallBigTarget1);
    reqAirBallIN(offset + param.mAirBallBigOffset2, pos + param.mAirBallBigTarget2);
    obj().soundSE().normal().start(0x321);
    Vector3 effectPos = obj().location().pos();
    effectPos += Vector3(param.mAirBallBigEffectOffset);
    obj().effect().normal().requestPD(static_cast<effect::Kind>(0x585), effectPos, Direction3::FRONT_TO_LEFT);
}

void StateShotAirBallBig::reqAirBallIN(const Vector2& offset, const Vector2& target) {
    const Param& param = obj().param().whispy();
    Vector2 pos = obj().location().pos().getXY();
    pos += offset;
    Vector2 speed = param.mAirBallBigSpeed;
    weapon::Desc desc(static_cast<weapon::Kind>(0xC), 1, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    desc._24 = target;
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::whispy
