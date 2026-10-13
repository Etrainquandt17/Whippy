#ifndef SCN_STEP_HERO_UTILITY_H
#define SCN_STEP_HERO_UTILITY_H

#include "scn/step/hero/ScriptKind.h"

namespace util {
template <typename T>
class ObjRefHandle;
}

namespace hel {
namespace math {
class Vector2;
}
}

namespace gobj {
struct MoveParamAccel;
struct MoveParamDecel;
struct MoveParamFall;
}

namespace scn {
namespace step {
namespace weapon {
class Weapon;
}
}
}

namespace scn {
namespace step {
namespace hero {

class Hero;

class Utility {
public:
    static bool IsFinalBattle(Hero& hero);
    static bool IsSeparateProcessMyTurn(const Hero& hero);
    static void ReqLandingStar(Hero& hero);
    static void ReqNakigoe(Hero& hero);
    static void ReqKakegoe(Hero& hero);
    static bool IsPressHDirKey(Hero& hero);
    static bool IsRidingItem(Hero& hero);
    static util::ObjRefHandle<weapon::Weapon> CreateEffectLocator(Hero& hero);
    static void ChangeStateWaitOrFall(Hero& hero);
    static void MoveDefault(Hero& hero);
    static void MoveDefaultNoOnIce(Hero& hero);
    static void MoveDefaultBrake(Hero& hero);
    static void MapCollReactDefaultAction(Hero& hero);
    static void AirActionInitSpeedV(Hero& hero);
    static void AirAttackInitSpeedV(Hero& hero);
    static bool CanWaterLanding(Hero& hero);
    static void CreateAirBall(Hero& hero, bool);
    static void SetSecondMoveIsValid(Hero& hero, bool isValid);
    static void MoveFromKeyState(Hero& hero, const gobj::MoveParamAccel& accel, const gobj::MoveParamDecel& decel,
                                 const gobj::MoveParamFall& fall);
    static void CreateWaterPistol(Hero& hero, const hel::math::Vector2& offset, bool);
    static void ReqWaterFloatOutProduce(Hero& hero);
    static void CloseGearParasol(Hero& hero);
    static void UpdateMoveTarget(Hero& hero);
    static void Vomit(Hero& hero, bool);
    static void ReleaseCarryItem(Hero& hero);
    static void SwitchBombDangerMotionInit(Hero& hero, ScriptKind script);
    static void SwitchBombDangerMotionProc(Hero& hero, ScriptKind script);
    static bool TryToPassThroughLandOnBombDanger(Hero& hero);
    static void MoveGuardDamage(Hero& hero);
    static bool IsPressHDirKeySameTarget(Hero& hero);
    static bool CanBoundByCheapAttack(Hero& hero);
    static void MoveGuard(Hero& hero);
    static bool ChkLogoutForce(Hero& hero);
    static void MoveDefaultAction(Hero& hero);
    static void MoveDefaultActionNoOnIce(Hero& hero);
    static void MoveDefaultBrakeNoOnIce(Hero& hero);
    static void RequestBubbleRollAction(Hero& hero, u32 frame);
    static bool IsSearchCollideNoStarEffect(Hero& hero);
    static void CorrectPosToInnerWorldCage(Hero& hero);
    static bool IsCollideCapturedEnemy(Hero& hero);
};

}
}
}

#endif
