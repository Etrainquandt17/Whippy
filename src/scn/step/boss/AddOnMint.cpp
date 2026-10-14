#include "scn/step/boss/AddOnMint.h"

#include "gobj/MintGearAnim.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "hel/mint/AddOnMathVector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StagingCtrl.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/bonkers/AddOnMint.h"
#include "scn/step/boss/doubter/AddOnMint.h"
#include "scn/step/boss/dubior/AddOnMint.h"
#include "scn/step/boss/fattybuffer/AddOnMint.h"
#include "scn/step/boss/galactaknight/AddOnMint.h"
#include "scn/step/boss/gigantedge/AddOnMint.h"
#include "scn/step/boss/goliath/AddOnMint.h"
#include "scn/step/boss/grandlowper/AddOnMint.h"
#include "scn/step/boss/hrd3/AddOnMint.h"
#include "scn/step/boss/hrd3pilot/AddOnMint.h"
#include "scn/step/boss/kingsdoo/AddOnMint.h"
#include "scn/step/boss/landia/AddOnMint.h"
#include "scn/step/boss/lowper/AddOnMint.h"
#include "scn/step/boss/mahoroabattle1/AddOnMint.h"
#include "scn/step/boss/mahoroabattle2/AddOnMint.h"
#include "scn/step/boss/mahoroaroah/AddOnMint.h"
#include "scn/step/boss/metalgeneral/AddOnMint.h"
#include "scn/step/boss/moundeath/AddOnMint.h"
#include "scn/step/boss/roah/AddOnMint.h"
#include "scn/step/boss/watergalboros/AddOnMint.h"
#include "scn/step/boss/whispy/AddOnMint.h"
#include "scn/step/boss/zankibble/AddOnMint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MintEffect.h"
#include "scn/step/hero/BossDemoCtrl.h"
#include "scn/step/hero/Manager.h"
#include "snd/MintSERequestor.h"

using g3d::ColorAnimFlashOp;
using hel::math::Vector2;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {

namespace {

void t_Effect_BindSuper() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().super());
}

void t_Effect_BindNormal() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().normal());
}

void t_Effect_BindNormalWarp() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().normalWarp());
}

void t_Effect_BindState() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().state());
}

void t_Effect_BindStateWarp() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().stateWarp());
}

void t_Effect_BindBack() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().back());
}

void t_Effect_BindFore() {
    chara::MintEffect::RegisterForce(MintBoss::Obj().effect().fore());
}

void t_SoundSE_BindNormal() {
    snd::MintSERequestor::RegisterForce(MintBoss::Obj().soundSE().normal());
}

void t_SoundSE_BindState() {
    snd::MintSERequestor::RegisterForce(MintBoss::Obj().soundSE().state());
}

void t_SoundSE_BindLoop() {
    snd::MintSERequestor::RegisterForce(MintBoss::Obj().soundSE().loop());
}

void t_Gear_Bind(int index) {
    gobj::MintGearAnim::RegisterForce(MintBoss::Obj().gearManager().gear(index).anim());
}

void t_AttackFlash_SetStart(int r, int g, int b, int a) {
    // A compound literal: with a named local the copy that is passed by value gets the other stack slot.
    MintBoss::Obj().flash().attack().setStart((GXColor){r, g, b, a});
}

void t_AttackFlash_SetContinue() {
    MintBoss::Obj().flash().attack().setContinue();
}

void t_AttackFlash_SetEnd(int r, int g, int b, int a) {
    MintBoss::Obj().flash().attack().setEnd((GXColor){r, g, b, a});
}

void t_AttackFlash_Cancel() {
    MintBoss::Obj().flash().attack().cancel();
}

void t_AttackFlash_SetAlphaIncRate(f32 rate) {
    MintBoss::Obj().flash().attack().setAlphaIncRate(rate);
}

void t_GuardFlash_SetIsValid(bool isValid) {
    MintBoss::Obj().flash().guard().setIsValid(isValid);
}

void t_CustomFlash_SetIsValid(bool isValid) {
    MintBoss::Obj().flash().custom().setIsValid(isValid);
}

void t_CustomFlash_SetColor(int r, int g, int b, int a) {
    MintBoss::Obj().flash().custom().setColor((GXColor){r, g, b, a});
}

void t_CustomFlash_SetOperation(int op) {
    MintBoss::Obj().flash().custom().setOperation(static_cast<ColorAnimFlashOp>(op));
}

bool t_Angry_Check() {
    return MintBoss::Obj().angry().check();
}

bool t_Angry_IsAngry() {
    return MintBoss::Obj().angry().isAngry();
}

bool t_Utility_IsHeroInRange(f32 left, f32 right, f32 bottom, f32 top) {
    return Utility::IsHeroInRange(MintBoss::Obj(), left, right, bottom, top);
}

bool t_Utility_IsHatedHeroInRange(f32 left, f32 right, f32 bottom, f32 top) {
    return Utility::IsHatedHeroInRange(MintBoss::Obj(), left, right, bottom, top);
}

bool t_Utility_IsHeroUpper(f32 height) {
    return Utility::IsHeroUpper(MintBoss::Obj(), height);
}

bool t_Utility_IsHeroSuper() {
    return Utility::IsHeroSuper(MintBoss::Obj());
}

bool t_Utility_IsHitWallFront() {
    return Utility::IsHitWallFront(MintBoss::Obj());
}

bool t_Utility_IsHitWallBack() {
    return Utility::IsHitWallBack(MintBoss::Obj());
}

bool t_Utility_IsFootStateGround() {
    return Utility::IsFootStateGround(MintBoss::Obj());
}

bool t_Utility_IsExistSuperElement() {
    return Utility::IsExistSuperElement(MintBoss::Obj());
}

f32 t_Utility_GetHitPointRate() {
    return Utility::GetHitPointRate(MintBoss::Obj());
}

int t_Utility_GetLevel() {
    return Utility::GetLevel(MintBoss::Obj());
}

bool t_Utility_IsVariationExtra() {
    return Utility::IsVariationExtra(MintBoss::Obj());
}

bool t_Utility_IsVariationBossRush() {
    return Utility::IsVariationBossRush(MintBoss::Obj());
}

void t_Utility_GenerateStarEffectPuff(f32 x, f32 y, f32 speedX, f32 speedY, int count) {
    Boss& obj = MintBoss::Obj();
    Utility::GenerateStarEffect(obj, Vector2(x, y), Vector2(speedX, speedY), map::BinEnemyVariation_StarPuff, count);
}

void t_Utility_GenerateStarEffectBound(f32 x, f32 y, f32 speedX, f32 speedY, int count) {
    Boss& obj = MintBoss::Obj();
    Utility::GenerateStarEffect(obj, Vector2(x, y), Vector2(speedX, speedY), map::BinEnemyVariation_StarBound, count);
}

void t_Utility_LoadBasePos() {
    hel::mint::AddOnMathVector3::Set(MintBoss::Obj().basePos().toVector3());
}

void t_Utility_LoadNearestHeroPos() {
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    hel::mint::AddOnMathVector3::Set(owner.comp().heroManager().getNearestPlayerPos(obj.location().pos()));
}

void t_Utility_LoadHatedHeroPos() {
    hel::mint::AddOnMathVector3::Set(Utility::GetHatedHeroPos(MintBoss::Obj()));
}

void t_Utility_SendBossDemoSignal(int kind) {
    MintBoss::Obj().comp().heroManager().bossDemoCtrl().setSignal(static_cast<hero::BossDemoSignalKind>(kind));
}

bool t_Utility_IsArena() {
    return Utility::IsArena(MintBoss::Obj());
}

int t_Utility_GetRetryCount() {
    return Utility::GetRetryCount(MintBoss::Obj());
}

void t_StagingCtrl_InitZoom(f32 x, f32 y, f32 zoom) {
    Boss& obj = MintBoss::Obj();
    obj.stagingCtrl().initZoom(Vector2(x, y), zoom);
}

void t_StagingCtrl_SetZoom(f32 x, f32 y, f32 zoom) {
    Boss& obj = MintBoss::Obj();
    obj.stagingCtrl().setZoom(Vector2(x, y), zoom);
}

void t_StagingCtrl_SetZoom(f32 zoom) {
    MintBoss::Obj().stagingCtrl().setZoom(zoom);
}

void t_StagingCtrl_UnsetZoom() {
    MintBoss::Obj().stagingCtrl().unsetZoom();
}

void t_StagingCtrl_ChangeZoomIntpRate(f32 rate) {
    MintBoss::Obj().stagingCtrl().changeZoomIntpRate(rate);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindSuper()", BindSuper, t_Effect_BindSuper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindNormal()", BindNormal, t_Effect_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindNormalWarp()", BindNormalWarp, t_Effect_BindNormalWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindState()", BindState, t_Effect_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindStateWarp()", BindStateWarp, t_Effect_BindStateWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindBack()", BindBack, t_Effect_BindBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Effect", "void BindFore()", BindFore, t_Effect_BindFore);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.SoundSE", "void BindNormal()", BindNormal, t_SoundSE_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.SoundSE", "void BindState()", BindState, t_SoundSE_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.SoundSE", "void BindLoop()", BindLoop, t_SoundSE_BindLoop);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Gear", "void Bind(int)", Bind, reinterpret_cast<void (*)(u32)>(t_Gear_Bind));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.AttackFlash", "void SetStart(int,int,int,int)", SetStart, t_AttackFlash_SetStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.AttackFlash", "void SetContinue()", SetContinue, t_AttackFlash_SetContinue);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.AttackFlash", "void SetEnd(int,int,int,int)", SetEnd, t_AttackFlash_SetEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.AttackFlash", "void Cancel()", Cancel, t_AttackFlash_Cancel);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.AttackFlash", "void SetAlphaIncRate(float)", SetAlphaIncRate, t_AttackFlash_SetAlphaIncRate);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GuardFlash", "void SetIsValid(bool)", SetIsValid, t_GuardFlash_SetIsValid);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.CustomFlash", "void SetIsValid(bool)", SetIsValid, t_CustomFlash_SetIsValid);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.CustomFlash", "void SetColor(int,int,int,int)", SetColor, t_CustomFlash_SetColor);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.CustomFlash", "void SetOperation(int)", SetOperation,
                         reinterpret_cast<void (*)(u32)>(t_CustomFlash_SetOperation));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Angry", "bool Check()", Check, t_Angry_Check);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Angry", "bool IsAngry()", IsAngry, t_Angry_IsAngry);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHeroInRange(float,float,float,float)", IsHeroInRange, t_Utility_IsHeroInRange);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHatedHeroInRange(float,float,float,float)", IsHatedHeroInRange,
                         t_Utility_IsHatedHeroInRange);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHeroUpper(float)", IsHeroUpper, t_Utility_IsHeroUpper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHeroSuper()", IsHeroSuper, t_Utility_IsHeroSuper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHitWallFront()", IsHitWallFront, t_Utility_IsHitWallFront);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsHitWallBack()", IsHitWallBack, t_Utility_IsHitWallBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsFootStateGround()", IsFootStateGround, t_Utility_IsFootStateGround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsExistSuperElement()", IsExistSuperElement, t_Utility_IsExistSuperElement);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "float GetHitPointRate()", GetHitPointRate, t_Utility_GetHitPointRate);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "int GetLevel()", GetLevel, t_Utility_GetLevel);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsVariationExtra()", IsVariationExtra, t_Utility_IsVariationExtra);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsVariationBossRush()", IsVariationBossRush, t_Utility_IsVariationBossRush);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void GenerateStarEffectPuff(float,float,float,float,int)", GenerateStarEffectPuff,
                         t_Utility_GenerateStarEffectPuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void GenerateStarEffectBound(float,float,float,float,int)", GenerateStarEffectBound,
                         t_Utility_GenerateStarEffectBound);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void LoadBasePos()", LoadBasePos, t_Utility_LoadBasePos);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void LoadNearestHeroPos()", LoadNearestHeroPos, t_Utility_LoadNearestHeroPos);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void LoadHatedHeroPos()", LoadHatedHeroPos, t_Utility_LoadHatedHeroPos);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "void SendBossDemoSignal(int)", SendBossDemoSignal,
                         reinterpret_cast<void (*)(u32)>(t_Utility_SendBossDemoSignal));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "bool IsArena()", IsArena, t_Utility_IsArena);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Utility", "int GetRetryCount()", GetRetryCount, t_Utility_GetRetryCount);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.StagingCtrl", "void InitZoom(float,float,float)", InitZoom, t_StagingCtrl_InitZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.StagingCtrl", "void SetZoom(float,float,float)", SetZoom,
                         static_cast<void (*)(f32, f32, f32)>(t_StagingCtrl_SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.StagingCtrl", "void SetZoom(float)", SetZoom, static_cast<void (*)(f32)>(t_StagingCtrl_SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.StagingCtrl", "void UnsetZoom()", UnsetZoom, t_StagingCtrl_UnsetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.StagingCtrl", "void ChangeZoomIntpRate(float)", ChangeZoomIntpRate, t_StagingCtrl_ChangeZoomIntpRate);

    bonkers::AddOnMint::RegisterAll(core);
    doubter::AddOnMint::RegisterAll(core);
    dubior::AddOnMint::RegisterAll(core);
    fattybuffer::AddOnMint::RegisterAll(core);
    galactaknight::AddOnMint::RegisterAll(core);
    gigantedge::AddOnMint::RegisterAll(core);
    goliath::AddOnMint::RegisterAll(core);
    grandlowper::AddOnMint::RegisterAll(core);
    hrd3::AddOnMint::RegisterAll(core);
    hrd3pilot::AddOnMint::RegisterAll(core);
    kingsdoo::AddOnMint::RegisterAll(core);
    landia::AddOnMint::RegisterAll(core);
    lowper::AddOnMint::RegisterAll(core);
    mahoroabattle1::AddOnMint::RegisterAll(core);
    mahoroabattle2::AddOnMint::RegisterAll(core);
    mahoroaroah::AddOnMint::RegisterAll(core);
    metalgeneral::AddOnMint::RegisterAll(core);
    moundeath::AddOnMint::RegisterAll(core);
    roah::AddOnMint::RegisterAll(core);
    watergalboros::AddOnMint::RegisterAll(core);
    whispy::AddOnMint::RegisterAll(core);
    zankibble::AddOnMint::RegisterAll(core);
}

}

}}}  // namespace scn::step::boss
