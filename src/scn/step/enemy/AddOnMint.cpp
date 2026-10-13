#include "scn/step/enemy/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "hel/mint/AddOnMathVector3.h"
#include "mintglue/WrapNative.h"
#include "revolution/gx/GXStruct.h"
#include "scn/step/chara/MintEffect.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/armordee/AddOnMint.h"
#include "scn/step/enemy/babut/AddOnMint.h"
#include "scn/step/enemy/barbar/AddOnMint.h"
#include "scn/step/enemy/bladeknight/AddOnMint.h"
#include "scn/step/enemy/blipper/AddOnMint.h"
#include "scn/step/enemy/bouncy/AddOnMint.h"
#include "scn/step/enemy/bowby/AddOnMint.h"
#include "scn/step/enemy/brontoburt/AddOnMint.h"
#include "scn/step/enemy/broomhatter/AddOnMint.h"
#include "scn/step/enemy/bulby/AddOnMint.h"
#include "scn/step/enemy/cappy/AddOnMint.h"
#include "scn/step/enemy/carrydee/AddOnMint.h"
#include "scn/step/enemy/chasekeydegout/AddOnMint.h"
#include "scn/step/enemy/chilly/AddOnMint.h"
#include "scn/step/enemy/clayn/AddOnMint.h"
#include "scn/step/enemy/common/AddOnMint.h"
#include "scn/step/enemy/como/AddOnMint.h"
#include "scn/step/enemy/degout/AddOnMint.h"
#include "scn/step/enemy/doubtersnake/AddOnMint.h"
#include "scn/step/enemy/dubiorjr/AddOnMint.h"
#include "scn/step/enemy/elec/AddOnMint.h"
#include "scn/step/enemy/fattybufferjr/AddOnMint.h"
#include "scn/step/enemy/flamer/AddOnMint.h"
#include "scn/step/enemy/galbo/AddOnMint.h"
#include "scn/step/enemy/gemra/AddOnMint.h"
#include "scn/step/enemy/gigatzo/AddOnMint.h"
#include "scn/step/enemy/glunk/AddOnMint.h"
#include "scn/step/enemy/hothead/AddOnMint.h"
#include "scn/step/enemy/juckle/AddOnMint.h"
#include "scn/step/enemy/kabu/AddOnMint.h"
#include "scn/step/enemy/knucklejoe/AddOnMint.h"
#include "scn/step/enemy/lanzer/AddOnMint.h"
#include "scn/step/enemy/larpa/AddOnMint.h"
#include "scn/step/enemy/leafan/AddOnMint.h"
#include "scn/step/enemy/leaper/AddOnMint.h"
#include "scn/step/enemy/liepa/AddOnMint.h"
#include "scn/step/enemy/lupa/AddOnMint.h"
#include "scn/step/enemy/mahoroahammer/AddOnMint.h"
#include "scn/step/enemy/mahoroamagicball/AddOnMint.h"
#include "scn/step/enemy/metalgeneralbit/AddOnMint.h"
#include "scn/step/enemy/metalgeneralthunder/AddOnMint.h"
#include "scn/step/enemy/mumbies/AddOnMint.h"
#include "scn/step/enemy/noddy/AddOnMint.h"
#include "scn/step/enemy/nruff/AddOnMint.h"
#include "scn/step/enemy/owgulf/AddOnMint.h"
#include "scn/step/enemy/pacto/AddOnMint.h"
#include "scn/step/enemy/pluid/AddOnMint.h"
#include "scn/step/enemy/poppybrojr/AddOnMint.h"
#include "scn/step/enemy/rocky/AddOnMint.h"
#include "scn/step/enemy/scarfy/AddOnMint.h"
#include "scn/step/enemy/sheld/AddOnMint.h"
#include "scn/step/enemy/shotzo/AddOnMint.h"
#include "scn/step/enemy/sirkibble/AddOnMint.h"
#include "scn/step/enemy/sisterbound/AddOnMint.h"
#include "scn/step/enemy/sodory/AddOnMint.h"
#include "scn/step/enemy/sparky/AddOnMint.h"
#include "scn/step/enemy/squishy/AddOnMint.h"
#include "scn/step/enemy/starman/AddOnMint.h"
#include "scn/step/enemy/tick/AddOnMint.h"
#include "scn/step/enemy/tsukikage/AddOnMint.h"
#include "scn/step/enemy/twister/AddOnMint.h"
#include "scn/step/enemy/waddledee/AddOnMint.h"
#include "scn/step/enemy/waddledoo/AddOnMint.h"
#include "scn/step/enemy/walf/AddOnMint.h"
#include "scn/step/enemy/walky/AddOnMint.h"
#include "scn/step/enemy/watergalbo/AddOnMint.h"
#include "scn/step/enemy/whippy/AddOnMint.h"
#include "snd/MintSERequestor.h"

namespace scn {
namespace step {
namespace enemy {

namespace {

void t_Effect_BindNormal() {
    chara::MintEffect::RegisterForce(MintEnemy::Obj()->effect().normal());
}

void t_Effect_BindState() {
    chara::MintEffect::RegisterForce(MintEnemy::Obj()->effect().state());
}

void t_Effect_BindSuper() {
    chara::MintEffect::RegisterForce(MintEnemy::Obj()->effect().super());
}

void t_SoundSE_BindNormal() {
    snd::MintSERequestor::RegisterForce(MintEnemy::Obj()->soundSE());
}

void t_SoundSE_BindState() {
    snd::MintSERequestor::RegisterForce(MintEnemy::Obj()->soundSEState());
}

void t_Flash_SetEnf1F(int r, int g, int b, int a) {
    GXColor color = {r, g, b, a};
    MintEnemy::Obj()->flash().setEnf1F(color);
}

f32 t_Utility_GetModelScaleBySizeType() {
    return Utility::GetModelScaleBySizeType(*MintEnemy::Obj());
}

bool t_Utility_IsNearestPlayerRight() {
    return Utility::IsNearestPlayerRight(*MintEnemy::Obj());
}

void t_Utility_SetTargetByDirType() {
    Utility::SetTargetByDirType(*MintEnemy::Obj());
}

void t_Utility_Turn() {
    Utility::Turn(*MintEnemy::Obj());
}

bool t_Utility_ChkCliff() {
    return Utility::ChkCliff(*MintEnemy::Obj());
}

void t_Utility_ChkCliffTurn() {
    Utility::ChkCliffTurn(*MintEnemy::Obj());
}

void t_Utility_ChkNururiTurn() {
    Utility::ChkNururiTurn(*MintEnemy::Obj());
}

void t_Utility_TurnHero() {
    Utility::TurnHero(*MintEnemy::Obj());
}

int t_Utility_Level() {
    return MintEnemy::Obj()->level();
}

void t_Utility_Suicide() {
    Utility::Suicide(*MintEnemy::Obj());
}

bool t_Utility_IsHeroInRange(f32 left, f32 right, f32 top, f32 bottom) {
    return Utility::IsHeroInRange(*MintEnemy::Obj(), left, right, top, bottom);
}

bool t_Utility_IsHeroInRangeByDir(f32 front, f32 back, f32 top, f32 bottom) {
    return Utility::IsHeroInRangeByDir(*MintEnemy::Obj(), front, back, top, bottom);
}

bool t_Utility_IsExistLand(f32 x, f32 y) {
    return Utility::IsExistLand(*MintEnemy::Obj(), x, y);
}

void t_Utility_GetDirVecByDirType() {
    hel::mint::AddOnMathVector3::Set(Utility::GetDirVecByDirType(*MintEnemy::Obj()));
}

bool t_Utility_IsFixDirType() {
    return Utility::IsFixDirType(*MintEnemy::Obj());
}

f32 t_Utility_GetRotByDirType() {
    return Utility::GetRotByDirType(*MintEnemy::Obj());
}

bool t_Utility_IsWaterGrid(f32 x, f32 y) {
    return Utility::IsWaterGrid(*MintEnemy::Obj(), x, y);
}

bool t_Utility_IsPlayerExist() {
    return Utility::IsPlayerExist(*MintEnemy::Obj());
}

bool t_Utility_IsCameraOut() {
    return Utility::IsCameraOut(*MintEnemy::Obj());
}

bool t_Utility_IsExistKeyCarryingHero() {
    return Utility::IsExistKeyCarryingHero(*MintEnemy::Obj());
}

bool t_Utility_IsExtra() {
    return Utility::IsExtra(*MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Effect", "void BindNormal()", BindNormal, t_Effect_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Effect", "void BindState()", BindState, t_Effect_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Effect", "void BindSuper()", BindSuper, t_Effect_BindSuper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SoundSE", "void BindNormal()", BindNormal, t_SoundSE_BindNormal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SoundSE", "void BindState()", BindState, t_SoundSE_BindState);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Flash", "void SetEnf1F(int,int,int,int)", SetEnf1F, t_Flash_SetEnf1F);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "float GetModelScaleBySizeType()", GetModelScaleBySizeType, t_Utility_GetModelScaleBySizeType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsNearestPlayerRight()", IsNearestPlayerRight, t_Utility_IsNearestPlayerRight);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void SetTargetByDirType()", SetTargetByDirType, t_Utility_SetTargetByDirType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void Turn()", Turn, t_Utility_Turn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool ChkCliff()", ChkCliff, t_Utility_ChkCliff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void ChkCliffTurn()", ChkCliffTurn, t_Utility_ChkCliffTurn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void ChkNururiTurn()", ChkNururiTurn, t_Utility_ChkNururiTurn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void TurnHero()", TurnHero, t_Utility_TurnHero);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "int Level()", Level, t_Utility_Level);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void Suicide()", Suicide, t_Utility_Suicide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsHeroInRange(float,float,float,float)", IsHeroInRange, t_Utility_IsHeroInRange);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsHeroInRangeByDir(float,float,float,float)", IsHeroInRangeByDir, t_Utility_IsHeroInRangeByDir);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsExistLand(float,float)", IsExistLand, t_Utility_IsExistLand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "void GetDirVecByDirType()", GetDirVecByDirType, t_Utility_GetDirVecByDirType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsFixDirType()", IsFixDirType, t_Utility_IsFixDirType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "float GetRotByDirType()", GetRotByDirType, t_Utility_GetRotByDirType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsWaterGrid(float,float)", IsWaterGrid, t_Utility_IsWaterGrid);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsPlayerExist()", IsPlayerExist, t_Utility_IsPlayerExist);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsCameraOut()", IsCameraOut, t_Utility_IsCameraOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsExistKeyCarryingHero()", IsExistKeyCarryingHero, t_Utility_IsExistKeyCarryingHero);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Utility", "bool IsExtra()", IsExtra, t_Utility_IsExtra);

    common::AddOnMint::RegisterAll(core);
    leafan::AddOnMint::RegisterAll(core);
    kabu::AddOnMint::RegisterAll(core);
    noddy::AddOnMint::RegisterAll(core);
    nruff::AddOnMint::RegisterAll(core);
    starman::AddOnMint::RegisterAll(core);
    bouncy::AddOnMint::RegisterAll(core);
    gigatzo::AddOnMint::RegisterAll(core);
    twister::AddOnMint::RegisterAll(core);
    como::AddOnMint::RegisterAll(core);
    rocky::AddOnMint::RegisterAll(core);
    sisterbound::AddOnMint::RegisterAll(core);
    waddledoo::AddOnMint::RegisterAll(core);
    doubtersnake::AddOnMint::RegisterAll(core);
    sparky::AddOnMint::RegisterAll(core);
    broomhatter::AddOnMint::RegisterAll(core);
    blipper::AddOnMint::RegisterAll(core);
    tick::AddOnMint::RegisterAll(core);
    bladeknight::AddOnMint::RegisterAll(core);
    watergalbo::AddOnMint::RegisterAll(core);
    whippy::AddOnMint::RegisterAll(core);
    babut::AddOnMint::RegisterAll(core);
    hothead::AddOnMint::RegisterAll(core);
    flamer::AddOnMint::RegisterAll(core);
    shotzo::AddOnMint::RegisterAll(core);
    mumbies::AddOnMint::RegisterAll(core);
    glunk::AddOnMint::RegisterAll(core);
    pacto::AddOnMint::RegisterAll(core);
    cappy::AddOnMint::RegisterAll(core);
    dubiorjr::AddOnMint::RegisterAll(core);
    poppybrojr::AddOnMint::RegisterAll(core);
    sirkibble::AddOnMint::RegisterAll(core);
    bulby::AddOnMint::RegisterAll(core);
    owgulf::AddOnMint::RegisterAll(core);
    juckle::AddOnMint::RegisterAll(core);
    pluid::AddOnMint::RegisterAll(core);
    bowby::AddOnMint::RegisterAll(core);
    chilly::AddOnMint::RegisterAll(core);
    degout::AddOnMint::RegisterAll(core);
    brontoburt::AddOnMint::RegisterAll(core);
    tsukikage::AddOnMint::RegisterAll(core);
    squishy::AddOnMint::RegisterAll(core);
    barbar::AddOnMint::RegisterAll(core);
    fattybufferjr::AddOnMint::RegisterAll(core);
    metalgeneralbit::AddOnMint::RegisterAll(core);
    metalgeneralthunder::AddOnMint::RegisterAll(core);
    elec::AddOnMint::RegisterAll(core);
    galbo::AddOnMint::RegisterAll(core);
    waddledee::AddOnMint::RegisterAll(core);
    walf::AddOnMint::RegisterAll(core);
    larpa::AddOnMint::RegisterAll(core);
    liepa::AddOnMint::RegisterAll(core);
    lupa::AddOnMint::RegisterAll(core);
    leaper::AddOnMint::RegisterAll(core);
    chasekeydegout::AddOnMint::RegisterAll(core);
    armordee::AddOnMint::RegisterAll(core);
    mahoroamagicball::AddOnMint::RegisterAll(core);
    carrydee::AddOnMint::RegisterAll(core);
    mahoroahammer::AddOnMint::RegisterAll(core);
    scarfy::AddOnMint::RegisterAll(core);
    sheld::AddOnMint::RegisterAll(core);
    knucklejoe::AddOnMint::RegisterAll(core);
    lanzer::AddOnMint::RegisterAll(core);
    gemra::AddOnMint::RegisterAll(core);
    clayn::AddOnMint::RegisterAll(core);
    walky::AddOnMint::RegisterAll(core);
    sodory::AddOnMint::RegisterAll(core);
}

}

}}}  // namespace scn::step::enemy
