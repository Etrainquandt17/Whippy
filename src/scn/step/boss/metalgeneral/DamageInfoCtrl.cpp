#include "scn/step/boss/metalgeneral/DamageInfoCtrl.h"

#include "app/Locale.h"
#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "std/min.h"

using app::Locale;
using app::Random;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

// The Korean build has one more effect ahead of the digits, the comma.
#ifdef VERSION_SUKK01
#define DIGIT_EFFECT(n) static_cast<effect::Kind>(0x61E + (n))
#else
#define DIGIT_EFFECT(n) static_cast<effect::Kind>(0x61D + (n))
#endif

const effect::Kind EffectName[] = {
    DIGIT_EFFECT(0), DIGIT_EFFECT(1), DIGIT_EFFECT(2), DIGIT_EFFECT(3), DIGIT_EFFECT(4),
    DIGIT_EFFECT(5), DIGIT_EFFECT(6), DIGIT_EFFECT(7), DIGIT_EFFECT(8), DIGIT_EFFECT(9),
};

struct Config {
    int mDamageMin;
    int mDamageMax;
    f32 mScale;
};

Config configTable[] = {
    { 0, 5, 0.65f }, { 6, 10, 0.75f }, { 11, 25, 0.85f }, { 26, 40, 1.0f }, { 41, 55, 1.1f }, { 56, 100, 1.2f },
};

inline f32 t_scale(u32 damage) {
    for (u32 i = 0; i < 6; i++) {
        if (configTable[i].mDamageMin <= damage && damage <= configTable[i].mDamageMax) {
            return configTable[i].mScale;
        }
    }
    return 1.0f;
}

}

DamageInfoCtrl::DamageInfoCtrl(Boss& boss) : mBoss(boss) {}

void DamageInfoCtrl::set(u32 damage) {
    const Param& param = mBoss.param().metalgeneral();
    u32 value = std::min<u32>(damage, configTable[5].mDamageMax);
    Vector3 pos = mBoss.model().model().nodes().at(5).worldTrans() + Vector3(param._2E8);
    Vector2 offset = Vector2::ALL_ONE;
    offset.x *= Random::RandF(-param.mDamageInfoRandX, param.mDamageInfoRandX);
    offset.y *= Random::RandF(-param.mDamageInfoRandY, param.mDamageInfoRandY);
    pos += offset.toVector3();
    f32 scale = t_scale(value);
    scale += Random::RandF(-param.mDamageInfoRandScale, param.mDamageInfoRandScale);
    u32 number = value * 10 + Random::Rand(-param.mDamageInfoRandNumber, param.mDamageInfoRandNumber - 1);
    if (number >= 1000) {
#ifdef VERSION_SUKK01
        u32 digit = number / 1000;
        if (Locale::GetRegion() == 2) {
            switch (Locale::GetLanguage()) {
            case 1:
                requestAddCommaDigit4(digit, pos, scale);
                break;
            case 2:
            case 3:
                requestAddSpaceDigit4(digit, pos, scale);
                break;
            default:
                request(digit, 4, pos, scale);
                break;
            }
        } else {
            request(digit, 4, pos, scale);
        }
#else
        request(number / 1000, 4, pos, scale);
#endif
    }
    if (number >= 100) {
        request(number % 1000 / 100, 3, pos, scale);
    }
    request(number % 100 / 10, 2, pos, scale);
    request(number % 10, 1, pos, scale);
}

void DamageInfoCtrl::request(u32 digit, u32 place, Vector3 pos, f32 scale) {
    const Param& param = mBoss.param().metalgeneral();
    Vector3 effectPos = pos;
    for (u32 i = 1; i < place; i++) {
        effectPos.x -= param.mDamageInfoDigitWidth * scale;
    }
    mBoss.effect().fore().requestP(EffectName[digit], effectPos, scale);
}

#ifdef VERSION_SUKK01
void DamageInfoCtrl::requestAddSpaceDigit4(u32 digit, Vector3 pos, f32 scale) {
    const Param& param = mBoss.param().metalgeneral();
    Vector3 effectPos = pos;
    for (u32 i = 0; i < 3; i++) {
        effectPos.x -= param.mDamageInfoDigitWidth * scale;
    }
    effectPos.x -= param.mDamageInfoSpaceWidth * scale;
    mBoss.effect().fore().requestP(EffectName[digit], effectPos, scale);
}

void DamageInfoCtrl::requestAddCommaDigit4(u32 digit, Vector3 pos, f32 scale) {
    const Param& param = mBoss.param().metalgeneral();
    Vector3 effectPos = pos;
    for (u32 i = 0; i < 2; i++) {
        effectPos.x -= param.mDamageInfoDigitWidth * scale;
    }
    effectPos.x -= param.mDamageInfoCommaWidth * scale;
    mBoss.effect().fore().requestP(static_cast<effect::Kind>(0x61D), effectPos, scale);
    effectPos.x -= param.mDamageInfoCommaWidth * scale;
    mBoss.effect().fore().requestP(EffectName[digit], effectPos, scale);
}
#endif

}}}}  // namespace scn::step::boss::metalgeneral
