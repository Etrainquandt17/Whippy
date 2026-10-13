#ifndef SCN_STEP_HERO_STATECHECKER_H
#define SCN_STEP_HERO_STATECHECKER_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class StateChecker {
public:
    void setRun(bool isRun) { mIsRun = isRun; }
    void setFloat(bool isFloat) { mIsFloat = isFloat; }
    void setSuperJump(bool isSuperJump) { (&mIsCarryBombDanger)[0x6C - 0x2C] = isSuperJump; }
    // TODO: a u32 at 0x14; StateSuperJump sets it to 14
    void set_14(u32 value) { *reinterpret_cast<u32*>(&mIsFloat + (0x14 - 0x9)) = value; }
    // TODO: a u32 at 0x5C; the name is a guess from setForbidCarryCatch() and StateCarryItemCatch::TryToChangeState
    bool isForbidCarryCatch() const { return *reinterpret_cast<const u32*>(&mIsCarryBombDanger + (0x5C - 0x2C)) != 0; }
    bool isRun() const { return mIsRun; }
    bool isFloat() const { return mIsFloat; }
    bool haveBomb() const { return mHaveBomb; }
    void setHaveBomb(bool have) { mHaveBomb = have; }
    bool isAbilityBombDanger() const { return mIsAbilityBombDanger; }
    void setAbilityBombDanger(bool danger) { mIsAbilityBombDanger = danger; }
    bool isBombDanger() const { return mIsAbilityBombDanger || mIsCarryBombDanger; }
    bool isCarryBombDanger() const { return mIsCarryBombDanger; }
    // TODO: a member at 0x2D, once the size of the class is known
    bool isHover() const { return (&mIsCarryBombDanger)[1]; }
    // TODO: a member at 0x59, the same way
    bool is_59() const { return (&mIsCarryBombDanger)[0x59 - 0x2C]; }
    // TODO: a member at 0xC, the same way
    bool isSquat() const { return (&mIsFloat)[0xC - 0x9]; }
    // TODO: a member at 0x44, the same way
    bool is_44() const { return (&mIsCarryBombDanger)[0x44 - 0x2C]; }
    // TODO: a member at 0x6C, the same way; the name is a guess from Piggyback::isRootSuperJump
    bool isSuperJump() const { return (&mIsCarryBombDanger)[0x6C - 0x2C]; }
    // TODO: a member at 0x1E, the same way
    void set_1e(bool flag) { (&mIsFloat)[0x1E - 0x9] = flag; }
    bool is_1e() const { return (&mIsFloat)[0x1E - 0x9]; }
    // TODO: a member at 0x29, the same way
    void setDemo(bool flag) { (&mIsFloat)[0x29 - 0x9] = flag; }
    void setIsForbidSpaceJump(bool flag) { (&mIsFloat)[0x1C - 0x9] = flag; }
    void set_40(bool flag) { (&mIsCarryBombDanger)[0x40 - 0x2C] = flag; }
    void setChallengeDoorWait(bool flag) { (&mIsCarryBombDanger)[0x44 - 0x2C] = flag; }
    void setDrinkAbility(bool flag) { (&mIsCarryBombDanger)[0x48 - 0x2C] = flag; }
    bool is_51() const { return (&mIsCarryBombDanger)[0x51 - 0x2C]; }
    void setPlancher(bool flag) { (&mIsFloat)[0xB - 0x9] = flag; }
    bool isPlancher() const { return (&mIsFloat)[0xB - 0x9]; }
    void set_4c(u32 value) { *reinterpret_cast<u32*>(&mIsCarryBombDanger + (0x4C - 0x2C)) = value; }
    void setHover(bool flag) { (&mIsCarryBombDanger)[1] = flag; }
    void setJumpStart(bool flag) { (&mIsFloat)[0xA - 0x9] = flag; }
    void set_64(u32 value) { *reinterpret_cast<u32*>(&mIsCarryBombDanger + (0x64 - 0x2C)) = value; }
    void setSquat(bool flag) { (&mIsFloat)[0xC - 0x9] = flag; }
    void setVacuumReceiverNoReset(bool flag) { (&mIsCarryBombDanger)[0x3F - 0x2C] = flag; }
    bool isSparkCharging() const { return (&mIsFloat)[0x28 - 0x9]; }
    void setWait(bool flag) { (&mIsCarryBombDanger)[0x43 - 0x2C] = flag; }
    void set_59(bool value) { (&mIsCarryBombDanger)[0x59 - 0x2C] = value; }
    bool is_60() const { return (&mIsCarryBombDanger)[0x60 - 0x2C]; }
    bool isJumpStart() const { return (&mIsFloat)[0xA - 0x9]; }
    // TODO: a member at 0x1D, the same way; cutter::StateCutterCatch enters on it
    bool is_1d() const { return (&mIsFloat)[0x1D - 0x9]; }
    void setStoneWait(bool flag) { (&mIsCarryBombDanger)[0x6D - 0x2C] = flag; }
    // TODO: a u32 at 0x68; ninja::StateHideGuard enters on it or on Guard::isGuard()
    bool is_68() const { return *reinterpret_cast<const u32*>(&mIsCarryBombDanger + (0x68 - 0x2C)) != 0; }
    // TODO: a u32 at 0x18; gimmick::StateRopeFlatWait refuses on it and sets it to 14 when it ends
    bool is_18() const { return *reinterpret_cast<const u32*>(&mIsFloat + (0x18 - 0x9)) != 0; }
    void set_18(u32 value) { *reinterpret_cast<u32*>(&mIsFloat + (0x18 - 0x9)) = value; }
    bool isForbidSpaceJump() const { return (&mIsFloat)[0x1C - 0x9]; }
    // TODO: u32 members at 0x20, 0x24 and 0x54, set and read by the cannon and warp star states
    void set_20(u32 value) { *reinterpret_cast<u32*>(&mIsFloat + (0x20 - 0x9)) = value; }
    u32 get_24() const { return *reinterpret_cast<const u32*>(&mIsFloat + (0x24 - 0x9)); }
    void set_24(u32 value) { *reinterpret_cast<u32*>(&mIsFloat + (0x24 - 0x9)) = value; }
    u32 get_54() const { return *reinterpret_cast<const u32*>(&mIsCarryBombDanger + (0x54 - 0x2C)); }
    // TODO: members at 0x3C and 0x46, the same way
    bool is_3c() const { return (&mIsCarryBombDanger)[0x3C - 0x2C]; }
    bool is_46() const { return (&mIsCarryBombDanger)[0x46 - 0x2C]; }
    void set_50(bool flag) { (&mIsCarryBombDanger)[0x50 - 0x2C] = flag; }
    void setScrewSuper(bool flag) { (&mIsFloat)[0x11 - 0x9] = flag; }
    // TODO: members at 0xD and 0xF; gimmick::StateCannonBlowWait sets 0xF when it starts and clears 0xD when it ends
    void set_d(bool flag) { (&mIsFloat)[0xD - 0x9] = flag; }
    void set_f(bool flag) { (&mIsFloat)[0xF - 0x9] = flag; }
    void setItemGet(bool flag) { (&mIsCarryBombDanger)[0x61 - 0x2C] = flag; }
    void setRopeFrat(bool flag) { (&mIsCarryBombDanger)[0x3E - 0x2C] = flag; }
    void setSkate(bool flag) { (&mIsFloat)[0x13 - 0x9] = flag; }
    void setCannon(bool flag) { (&mIsFloat)[0xD - 0x9] = flag; }
    void setCannonLaunch(bool flag) { (&mIsFloat)[0xE - 0x9] = flag; }
    void setCannonBlow(bool flag) { (&mIsFloat)[0xF - 0x9] = flag; }
    void setCannonBlowLaunch(bool flag) { (&mIsFloat)[0x10 - 0x9] = flag; }
    void clearLaunchCannonIndex();

private:
    u8 _0[0x8];
    bool mIsRun;
    bool mIsFloat;
    u8 _A[0x20];
    bool mHaveBomb;
    bool mIsAbilityBombDanger;
    bool mIsCarryBombDanger;
};

}}}  // namespace scn::step::hero

#endif
