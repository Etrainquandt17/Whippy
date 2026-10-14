#include "scn/step/boss/whispy/StateShotAirBallTornado.h"

#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjList.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateShotAirBallTornado::StateShotAirBallTornado(Boss* boss, u32 count, u32 intervalFirst, u32 interval)
    : StateShotAirBallBase(boss, count, intervalFirst, interval), mSpeedAdd(0.0f) {}

void StateShotAirBallTornado::reqAirBall() {
    const Param& param = obj().param().whispy();
    Vector2 pos = obj().location().pos().getXY();
    pos += param.mTornadoOffset;
    Vector2 speed = param.mTornadoSpeed;
    speed.x += mSpeedAdd;
    weapon::Desc desc(static_cast<weapon::Kind>(0x53), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().soundSE().normal().start(0x31D);
    u32 label = obj().angry().isAngry() ? 0x310 : 0x30F;
    obj().soundSE().normal().start(label);
    Vector3 effectPos = obj().location().pos();
    effectPos += Vector3(param.mTornadoEffectOffset);
    obj().effect().normal().requestPD(static_cast<effect::Kind>(0x585), effectPos, Direction3::FRONT_TO_LEFT);
    mSpeedAdd += param.mTornadoSpeedAdd;
}

}}}}  // namespace scn::step::boss::whispy
