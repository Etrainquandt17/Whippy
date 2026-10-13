#ifndef SCN_STEP_HERO_MINTUTILITY_H
#define SCN_STEP_HERO_MINTUTILITY_H

#include "scn/step/effect/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace MintUtility {

bool IsMainPlayer();
bool IsKirby();
bool IsMeta();
bool IsDedede();
bool IsDee();
void LoadPos();
void LoadDir();
void LoadModelDir();
void LoadDirFollowFloor();
void ReqLandingStar();
void ReqNakigoe();
void ReqKakegoe();
bool IsPinch();
bool IsInWater();
int ShakeChargePower();
bool IsInvisible();
bool IsPressHDirKey();
bool IsOnIce();
bool IsExistPiggybackChild();
bool IsExistCarryItem();
bool IsMainPlayerRight();
void SetIsDirRight(bool value);
bool IsDirRight();
bool IsHidDisable();
bool IsBossDemoSilent();
bool IsSeparateProcessMyTurn();
bool IsHaveCandle();
int PlayerCount();
void AddAttackGearNode3(u32 arg0, u32 arg1, f32 arg2);
void AddAttackGearNode5(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4);
void AddAttackGearNode7(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void AddAttackGearNode8(u32 arg0, u32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, bool arg7);
void RequestEffectGearNodeN(effect::Kind arg0, u32 arg1);
void RequestEffectGearNodeNS(effect::Kind arg0, u32 arg1, f32 arg2);
void RequestEffectGearNodeNO(effect::Kind arg0, u32 arg1);
void RequestEffectGearNodeNOS(effect::Kind arg0, u32 arg1, f32 arg2);
void RequestEffectGearNodeND(effect::Kind arg0, u32 arg1);
void RequestEffectGearNodeNDS(effect::Kind arg0, u32 arg1, f32 arg2);
void RequestEffectGearNodeNDO(effect::Kind arg0, u32 arg1);
void RequestEffectGearNodeNDOS(effect::Kind arg0, u32 arg1, f32 arg2);

}}}}  // namespace scn::step::hero::MintUtility

#endif
