#include "scn/step/hero/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/chara/MintEffect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintGear.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/MintAbilityManager.h"
#include "scn/step/hero/MintClearDanceSync.h"
#include "scn/step/hero/MintFloaterRotCtrl.h"
#include "scn/step/hero/MintGatherItem.h"
#include "scn/step/hero/MintHid.h"
#include "scn/step/hero/MintHidRumble.h"
#include "scn/step/hero/MintInvincible.h"
#include "scn/step/hero/MintLandAttribute.h"
#include "scn/step/hero/MintObjColl.h"
#include "scn/step/hero/MintScriptData.h"
#include "scn/step/hero/MintSlopeFit.h"
#include "scn/step/hero/MintSquash.h"
#include "scn/step/hero/MintStagingCtrl.h"
#include "scn/step/hero/MintStateChecker.h"
#include "scn/step/hero/MintUtility.h"
#include "scn/step/hero/supersword/MintSwordSelector.h"
#include "snd/MintSERequestor.h"

namespace scn {
namespace step {
namespace hero {

namespace {

void t_Effect_BindNormal() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._8);
}

void t_Effect_BindNormalWarp() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._30);
}

void t_Effect_BindState() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._58);
}

void t_Effect_BindState2() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._80);
}

void t_Effect_BindStateWarp() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._A8);
}

void t_Effect_BindMighty() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._D0);
}

void t_Effect_BindOther() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._F8);
}

void t_Effect_BindSuper() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._120);
}

void t_Effect_BindWater() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._148);
}

void t_Effect_BindWaterState() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._170);
}

void t_Effect_BindWaterWarp() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._198);
}

void t_Effect_BindAbility() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._1C0);
}

void t_Effect_BindNonStop() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._1E8);
}

void t_Effect_BindNonStopFore() {
    chara::MintEffect::RegisterForce(MintHero::Obj().effect()._210);
}

chara::MintEffect t_Effect_Normal() {
    return MintHero::Obj().effect()._8.mint();
}

chara::MintEffect t_Effect_NormalWarp() {
    return MintHero::Obj().effect()._30.mint();
}

chara::MintEffect t_Effect_State() {
    return MintHero::Obj().effect()._58.mint();
}

chara::MintEffect t_Effect_State2() {
    return MintHero::Obj().effect()._80.mint();
}

chara::MintEffect t_Effect_StateWarp() {
    return MintHero::Obj().effect()._A8.mint();
}

chara::MintEffect t_Effect_Mighty() {
    return MintHero::Obj().effect()._D0.mint();
}

chara::MintEffect t_Effect_Other() {
    return MintHero::Obj().effect()._F8.mint();
}

chara::MintEffect t_Effect_Super() {
    return MintHero::Obj().effect()._120.mint();
}

chara::MintEffect t_Effect_WaterWarp() {
    return MintHero::Obj().effect()._198.mint();
}

chara::MintEffect t_Effect_Ability() {
    return MintHero::Obj().effect()._1C0.mint();
}

chara::MintEffect t_Effect_NonStop() {
    return MintHero::Obj().effect()._1E8.mint();
}

chara::MintEffect t_Effect_NonStopFore() {
    return MintHero::Obj().effect()._210.mint();
}

void t_SoundSE_BindNormal() {
    snd::MintSERequestor::RegisterForce(MintHero::Obj().soundSE()._4);
}

void t_SoundSE_BindLoop() {
    snd::MintSERequestor::RegisterForce(MintHero::Obj().soundSE()._78);
}

void t_SoundSE_BindState() {
    snd::MintSERequestor::RegisterForce(MintHero::Obj().soundSE()._EC);
}

void t_SoundSE_BindNonStop() {
    snd::MintSERequestor::RegisterForce(MintHero::Obj().soundSE()._160);
}

void t_SoundSE_BindVacuum() {
    snd::MintSERequestor::RegisterForce(MintHero::Obj().soundSE()._2BC);
}

void t_Model_BindGearHat() {
    MintGear::RegisterForce(MintHero::Obj().model()._378);
}

void t_Model_BindGearHat2() {
    MintGear::RegisterForce(MintHero::Obj().model()._834);
}

void t_Model_BindGearRHand() {
    MintGear::RegisterForce(MintHero::Obj().model()._CF0);
}

void t_Model_BindGearLHand() {
    MintGear::RegisterForce(MintHero::Obj().model()._11AC);
}

void t_Model_BindGearRot() {
    MintGear::RegisterForce(MintHero::Obj().model()._1668);
}

void t_Model_BindGearTop() {
    MintGear::RegisterForce(MintHero::Obj().model()._1B24);
}

void t_Model_BindGearGoggle() {
    MintGear::RegisterForce(MintHero::Obj().model()._1FE0);
}

void t_Model_BindGearFloater() {
    MintGear::RegisterForce(MintHero::Obj().model()._249C);
}

void t_Model_BindGearWarpStar() {
    MintGear::RegisterForce(MintHero::Obj().model()._2958);
}

MintGear t_Model_GearHat() {
    return MintHero::Obj().model()._378.mint();
}

MintGear t_Model_GearHat2() {
    return MintHero::Obj().model()._834.mint();
}

MintGear t_Model_GearRHand() {
    return MintHero::Obj().model()._CF0.mint();
}

MintGear t_Model_GearLHand() {
    return MintHero::Obj().model()._11AC.mint();
}

MintGear t_Model_GearRot() {
    return MintHero::Obj().model()._1668.mint();
}

MintGear t_Model_GearTop() {
    return MintHero::Obj().model()._1B24.mint();
}

MintGear t_Model_GearGoggle() {
    return MintHero::Obj().model()._1FE0.mint();
}

MintGear t_Model_GearFloater() {
    return MintHero::Obj().model()._249C.mint();
}

MintGear t_Model_GearWarpStar() {
    return MintHero::Obj().model()._2958.mint();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindNormal()", BindNormal, &t_Effect_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindNormalWarp()", BindNormalWarp, &t_Effect_BindNormalWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindState()", BindState, &t_Effect_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindState2()", BindState2, &t_Effect_BindState2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindStateWarp()", BindStateWarp, &t_Effect_BindStateWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindMighty()", BindMighty, &t_Effect_BindMighty);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindOther()", BindOther, &t_Effect_BindOther);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindSuper()", BindSuper, &t_Effect_BindSuper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindWater()", BindWater, &t_Effect_BindWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindWaterState()", BindWaterState, &t_Effect_BindWaterState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindWaterWarp()", BindWaterWarp, &t_Effect_BindWaterWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindAbility()", BindAbility, &t_Effect_BindAbility);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindNonStop()", BindNonStop, &t_Effect_BindNonStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "void BindNonStopFore()", BindNonStopFore, &t_Effect_BindNonStopFore);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect Normal()", Normal, &t_Effect_Normal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect NormalWarp()", NormalWarp, &t_Effect_NormalWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect State()", State, &t_Effect_State);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect State2()", State2, &t_Effect_State2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect StateWarp()", StateWarp, &t_Effect_StateWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect Mighty()", Mighty, &t_Effect_Mighty);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect Other()", Other, &t_Effect_Other);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect Super()", Super, &t_Effect_Super);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect WaterWarp()", WaterWarp, &t_Effect_WaterWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect Ability()", Ability, &t_Effect_Ability);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect NonStop()", NonStop, &t_Effect_NonStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Effect", "Scn.Step.Chara.Effect NonStopFore()", NonStopFore, &t_Effect_NonStopFore);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsMainPlayer()", IsMainPlayer, static_cast<bool (*)()>(&MintUtility::IsMainPlayer));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsKirby()", IsKirby, static_cast<bool (*)()>(&MintUtility::IsKirby));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsMeta()", IsMeta, static_cast<bool (*)()>(&MintUtility::IsMeta));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsDedede()", IsDedede, static_cast<bool (*)()>(&MintUtility::IsDedede));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsDee()", IsDee, static_cast<bool (*)()>(&MintUtility::IsDee));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void LoadPos()", LoadPos, static_cast<void (*)()>(&MintUtility::LoadPos));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void LoadDir()", LoadDir, static_cast<void (*)()>(&MintUtility::LoadDir));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void LoadModelDir()", LoadModelDir, static_cast<void (*)()>(&MintUtility::LoadModelDir));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void LoadDirFollowFloor()", LoadDirFollowFloor,
                         static_cast<void (*)()>(&MintUtility::LoadDirFollowFloor));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void ReqLandingStar()", ReqLandingStar,
                         static_cast<void (*)()>(&MintUtility::ReqLandingStar));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void ReqNakigoe()", ReqNakigoe, static_cast<void (*)()>(&MintUtility::ReqNakigoe));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void ReqKakegoe()", ReqKakegoe, static_cast<void (*)()>(&MintUtility::ReqKakegoe));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsPinch()", IsPinch, static_cast<bool (*)()>(&MintUtility::IsPinch));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsInWater()", IsInWater, static_cast<bool (*)()>(&MintUtility::IsInWater));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "int ShakeChargePower()", ShakeChargePower,
                         static_cast<int (*)()>(&MintUtility::ShakeChargePower));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsInvisible()", IsInvisible, static_cast<bool (*)()>(&MintUtility::IsInvisible));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsPressHDirKey()", IsPressHDirKey,
                         static_cast<bool (*)()>(&MintUtility::IsPressHDirKey));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsOnIce()", IsOnIce, static_cast<bool (*)()>(&MintUtility::IsOnIce));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsExistPiggybackChild()", IsExistPiggybackChild,
                         static_cast<bool (*)()>(&MintUtility::IsExistPiggybackChild));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsExistCarryItem()", IsExistCarryItem,
                         static_cast<bool (*)()>(&MintUtility::IsExistCarryItem));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsMainPlayerRight()", IsMainPlayerRight,
                         static_cast<bool (*)()>(&MintUtility::IsMainPlayerRight));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void SetIsDirRight(bool)", SetIsDirRight,
                         static_cast<void (*)(bool)>(&MintUtility::SetIsDirRight));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsDirRight()", IsDirRight, static_cast<bool (*)()>(&MintUtility::IsDirRight));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsHidDisable()", IsHidDisable, static_cast<bool (*)()>(&MintUtility::IsHidDisable));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsBossDemoSilent()", IsBossDemoSilent,
                         static_cast<bool (*)()>(&MintUtility::IsBossDemoSilent));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsSeparateProcessMyTurn()", IsSeparateProcessMyTurn,
                         static_cast<bool (*)()>(&MintUtility::IsSeparateProcessMyTurn));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "bool IsHaveCandle()", IsHaveCandle, static_cast<bool (*)()>(&MintUtility::IsHaveCandle));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "int PlayerCount()", PlayerCount, static_cast<int (*)()>(&MintUtility::PlayerCount));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void AddAttackGearNode3(int,int,float)", AddAttackGearNode3,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(u32, u32, f32)>(&MintUtility::AddAttackGearNode3)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void AddAttackGearNode5(int,int,float,float,float)", AddAttackGearNode5,
                         static_cast<void (*)(u32, u32, f32, f32, f32)>(&MintUtility::AddAttackGearNode5));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void AddAttackGearNode7(int,int,float,float,float,float,float)", AddAttackGearNode7,
                         static_cast<void (*)(u32, u32, f32, f32, f32, f32, f32)>(&MintUtility::AddAttackGearNode7));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void AddAttackGearNode8(int,int,float,float,float,float,float,bool)", AddAttackGearNode8,
                         static_cast<void (*)(u32, u32, f32, f32, f32, f32, f32, bool)>(&MintUtility::AddAttackGearNode8));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeN(int,int)", RequestEffectGearNodeN,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(effect::Kind, u32)>(&MintUtility::RequestEffectGearNodeN)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNS(int,int,float)", RequestEffectGearNodeNS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(effect::Kind, u32, f32)>(&MintUtility::RequestEffectGearNodeNS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNO(int,int)", RequestEffectGearNodeNO,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(effect::Kind, u32)>(&MintUtility::RequestEffectGearNodeNO)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNOS(int,int,float)", RequestEffectGearNodeNOS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(effect::Kind, u32, f32)>(&MintUtility::RequestEffectGearNodeNOS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeND(int,int)", RequestEffectGearNodeND,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(effect::Kind, u32)>(&MintUtility::RequestEffectGearNodeND)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNDS(int,int,float)", RequestEffectGearNodeNDS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(effect::Kind, u32, f32)>(&MintUtility::RequestEffectGearNodeNDS)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNDO(int,int)", RequestEffectGearNodeNDO,
                         reinterpret_cast<void (*)(int, int)>(static_cast<void (*)(effect::Kind, u32)>(&MintUtility::RequestEffectGearNodeNDO)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Utility", "void RequestEffectGearNodeNDOS(int,int,float)", RequestEffectGearNodeNDOS,
                         reinterpret_cast<void (*)(int, int, f32)>(static_cast<void (*)(effect::Kind, u32, f32)>(&MintUtility::RequestEffectGearNodeNDOS)));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SoundSE", "void BindNormal()", BindNormal, &t_SoundSE_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SoundSE", "void BindLoop()", BindLoop, &t_SoundSE_BindLoop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SoundSE", "void BindState()", BindState, &t_SoundSE_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SoundSE", "void BindNonStop()", BindNonStop, &t_SoundSE_BindNonStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SoundSE", "void BindVacuum()", BindVacuum, &t_SoundSE_BindVacuum);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SlopeFit", "void SetValid(bool)", SetValid, static_cast<void (*)(bool)>(&MintSlopeFit::SetValid));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SlopeFit", "void SetIntpRate(float)", SetIntpRate,
                         static_cast<void (*)(f32)>(&MintSlopeFit::SetIntpRate));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SlopeFit", "void SetAffectRate(float)", SetAffectRate,
                         static_cast<void (*)(f32)>(&MintSlopeFit::SetAffectRate));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ObjColl", "void SetBodyCollDefault()", SetBodyCollDefault,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollDefault));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ObjColl", "void SetBodyCollBig()", SetBodyCollBig,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollBig));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ObjColl", "void SetBodyCollSquat()", SetBodyCollSquat,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollSquat));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ObjColl", "void SetBodyCollJump()", SetBodyCollJump,
                         static_cast<void (*)()>(&MintObjColl::SetBodyCollJump));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ScriptData", "void SetFlipFoot(bool)", SetFlipFoot,
                         static_cast<void (*)(bool)>(&MintScriptData::SetFlipFoot));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ScriptData", "bool GetFlipFoot()", GetFlipFoot, static_cast<bool (*)()>(&MintScriptData::GetFlipFoot));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StateChecker", "bool IsRun()", IsRun, static_cast<bool (*)()>(&MintStateChecker::IsRun));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StateChecker", "bool IsFloat()", IsFloat, static_cast<bool (*)()>(&MintStateChecker::IsFloat));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StateChecker", "bool IsCarryBombDanger()", IsCarryBombDanger,
                         static_cast<bool (*)()>(&MintStateChecker::IsCarryBombDanger));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StateChecker", "bool IsHover()", IsHover, static_cast<bool (*)()>(&MintStateChecker::IsHover));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "bool IsSuper()", IsSuper, static_cast<bool (*)()>(&MintAbilityManager::IsSuper));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "int AbilityKind()", AbilityKind,
                         static_cast<int (*)()>(&MintAbilityManager::AbilityKind));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "void SuperBGMRequest()", SuperBGMRequest,
                         static_cast<void (*)()>(&MintAbilityManager::SuperBGMRequest));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "void SuperBGMUnrequest()", SuperBGMUnrequest,
                         static_cast<void (*)()>(&MintAbilityManager::SuperBGMUnrequest));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "bool CanSuperBGMRequest()", CanSuperBGMRequest,
                         static_cast<bool (*)()>(&MintAbilityManager::CanSuperBGMRequest));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "int GetUseCount()", GetUseCount,
                         static_cast<int (*)()>(&MintAbilityManager::GetUseCount));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.AbilityManager", "bool IsOnGrandLowperBattle()", IsOnGrandLowperBattle,
                         static_cast<bool (*)()>(&MintAbilityManager::IsOnGrandLowperBattle));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearHat()", BindGearHat, &t_Model_BindGearHat);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearHat2()", BindGearHat2, &t_Model_BindGearHat2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearRHand()", BindGearRHand, &t_Model_BindGearRHand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearLHand()", BindGearLHand, &t_Model_BindGearLHand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearRot()", BindGearRot, &t_Model_BindGearRot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearTop()", BindGearTop, &t_Model_BindGearTop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearGoggle()", BindGearGoggle, &t_Model_BindGearGoggle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearFloater()", BindGearFloater, &t_Model_BindGearFloater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "void BindGearWarpStar()", BindGearWarpStar, &t_Model_BindGearWarpStar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearHat()", GearHat, &t_Model_GearHat);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearHat2()", GearHat2, &t_Model_GearHat2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearRHand()", GearRHand, &t_Model_GearRHand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearLHand()", GearLHand, &t_Model_GearLHand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearRot()", GearRot, &t_Model_GearRot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearTop()", GearTop, &t_Model_GearTop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearGoggle()", GearGoggle, &t_Model_GearGoggle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearFloater()", GearFloater, &t_Model_GearFloater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Model", "Scn.Step.Hero.Gear GearWarpStar()", GearWarpStar, &t_Model_GearWarpStar);

    core.addNativePod("Scn.Step.Hero.Gear", sizeof(MintGear));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "void setVisibility(bool)const", setVisibility, &MintGear::setVisibility);
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "void setNodeVisibility(int,bool)const", setNodeVisibility, &MintGear::setNodeVisibility);
    // The game binds this as a method that takes a bool, so the wrapper reads an argument scripts never pass.
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "bool isAnimExist()const", isAnimExist,
                           reinterpret_cast<bool (MintGear::*)(bool) const>(&MintGear::isAnimExist));
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "GObj.GearAnim anim()const", anim, &MintGear::anim);
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "Scn.Step.Chara.Effect effect()const", effect, &MintGear::effect);
    MINT_NATIVE_POD_METHOD(core, "Scn.Step.Hero.Gear", "Scn.Step.Chara.Effect effectWarp()const", effectWarp, &MintGear::effectWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Gear", "void SetVisibility(bool)", SetVisibility,
                         static_cast<void (*)(bool)>(&MintGear::SetVisibility));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Gear", "void SetNodeVisibility(int,bool)", SetNodeVisibility,
                         static_cast<void (*)(u32, bool)>(&MintGear::SetNodeVisibility));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Gear", "void LoadNode(int)", LoadNode, static_cast<void (*)(u32)>(&MintGear::LoadNode));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Gear", "void BindEffect()", BindEffect, static_cast<void (*)()>(&MintGear::BindEffect));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Gear", "void BindEffectWarp()", BindEffectWarp, static_cast<void (*)()>(&MintGear::BindEffectWarp));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.GatherItem", "void Add(float,float,float,float)", Add,
                         static_cast<void (*)(f32, f32, f32, f32)>(&MintGatherItem::Add));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.GatherItem", "void Clear()", Clear, static_cast<void (*)()>(&MintGatherItem::Clear));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Invincible", "void Set(int)", Set,
                         reinterpret_cast<void (*)(u32)>(static_cast<void (*)(int)>(&MintInvincible::Set)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Invincible", "void SetPerm()", SetPerm, static_cast<void (*)()>(&MintInvincible::SetPerm));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Invincible", "void UnsetPerm()", UnsetPerm, static_cast<void (*)()>(&MintInvincible::UnsetPerm));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Invincible", "bool IsMighty()", IsMighty, static_cast<bool (*)()>(&MintInvincible::IsMighty));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Hid", "bool IsHold(int)", IsHold,
                         reinterpret_cast<bool (*)(int)>(static_cast<bool (*)(u32)>(&MintHid::IsHold)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Hid", "bool IsTrigger(int)", IsTrigger,
                         reinterpret_cast<bool (*)(int)>(static_cast<bool (*)(u32)>(&MintHid::IsTrigger)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Hid", "void SetAutoInputHold(int)", SetAutoInputHold,
                         static_cast<void (*)(u32)>(&MintHid::SetAutoInputHold));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.HidRumble", "void Start(int)", Start,
                         reinterpret_cast<void (*)(u32)>(static_cast<void (*)(int)>(&MintHidRumble::Start)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.HidRumble", "void Stop()", Stop, static_cast<void (*)()>(&MintHidRumble::Stop));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Squash", "void SetTarget(float,float,float,float)", SetTarget,
                         static_cast<void (*)(f32, f32, f32, f32)>(&MintSquash::SetTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.Squash", "void ResetTarget(float)", ResetTarget, static_cast<void (*)(f32)>(&MintSquash::ResetTarget));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.LandAttribute", "void ReqEffectL(float,float)", ReqEffectL,
                         static_cast<void (*)(f32, f32)>(&MintLandAttribute::ReqEffectL));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.LandAttribute", "void ReqEffectS(float,float)", ReqEffectS,
                         static_cast<void (*)(f32, f32)>(&MintLandAttribute::ReqEffectS));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.LandAttribute", "void ReqEffectLanding(float,float)", ReqEffectLanding,
                         static_cast<void (*)(f32, f32)>(&MintLandAttribute::ReqEffectLanding));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.LandAttribute", "void ReqSE()", ReqSE, static_cast<void (*)()>(&MintLandAttribute::ReqSE));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.LandAttribute", "int AttributeType()", AttributeType,
                         static_cast<int (*)()>(&MintLandAttribute::AttributeType));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StagingCtrl", "void SetZoom(float,float,float)", SetZoom,
                         static_cast<void (*)(f32, f32, f32)>(&MintStagingCtrl::SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StagingCtrl", "void SetZoom(float)", SetZoom, static_cast<void (*)(f32)>(&MintStagingCtrl::SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StagingCtrl", "void UnsetZoom()", UnsetZoom, static_cast<void (*)()>(&MintStagingCtrl::UnsetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StagingCtrl", "void SetCamRot(float,float)", SetCamRot,
                         static_cast<void (*)(f32, f32)>(&MintStagingCtrl::SetCamRot));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.StagingCtrl", "void UnsetCamRot()", UnsetCamRot,
                         static_cast<void (*)()>(&MintStagingCtrl::UnsetCamRot));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SuperSword.SwordSelector", "void SetKind(int)", SetKind,
                         reinterpret_cast<void (*)(u32)>(static_cast<void (*)(int)>(&supersword::MintSwordSelector::SetKind)));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.SuperSword.SwordSelector", "void SetRareTryCount(int)", SetRareTryCount,
                         reinterpret_cast<void (*)(u32)>(static_cast<void (*)(int)>(&supersword::MintSwordSelector::SetRareTryCount)));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "float GetRotV()", GetRotV, static_cast<f32 (*)()>(&MintFloaterRotCtrl::GetRotV));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "void InitRotV(float)", InitRotV,
                         static_cast<void (*)(f32)>(&MintFloaterRotCtrl::InitRotV));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "void SetRotVTarget(float)", SetRotVTarget,
                         static_cast<void (*)(f32)>(&MintFloaterRotCtrl::SetRotVTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "void ResetRotVTarget()", ResetRotVTarget,
                         static_cast<void (*)()>(&MintFloaterRotCtrl::ResetRotVTarget));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "void SetRotVIntpRate(float)", SetRotVIntpRate,
                         static_cast<void (*)(f32)>(&MintFloaterRotCtrl::SetRotVIntpRate));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.FloaterRotCtrl", "void ResetRotVIntpRate()", ResetRotVIntpRate,
                         static_cast<void (*)()>(&MintFloaterRotCtrl::ResetRotVIntpRate));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ClearDanceSync", "bool IsSync()", IsSync, static_cast<bool (*)()>(&MintClearDanceSync::IsSync));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ClearDanceSync", "int FirstAnim()", FirstAnim, static_cast<int (*)()>(&MintClearDanceSync::FirstAnim));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ClearDanceSync", "int SecondAnim()", SecondAnim,
                         static_cast<int (*)()>(&MintClearDanceSync::SecondAnim));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ClearDanceSync", "int ThirdAnim()", ThirdAnim, static_cast<int (*)()>(&MintClearDanceSync::ThirdAnim));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Hero.ClearDanceSync", "int FinishAnim()", FinishAnim,
                         static_cast<int (*)()>(&MintClearDanceSync::FinishAnim));
}

}}}}  // namespace scn::step::hero::AddOnMint
