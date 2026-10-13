#include "mintglue/Scn__Title__Commander.h"

#include "mintglue/WrapNative.h"
#include "scn/title/Commander.h"

namespace mintglue {
namespace Scn__Title__Commander {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "int CurrentFrame()", CurrentFrame, &scn::title::Commander::CurrentFrame);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void SetFrame(int)", SetFrame, &scn::title::Commander::SetFrame);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void SceneAnimStart()", SceneAnimStart, &scn::title::Commander::SceneAnimStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void SceneAnimStop()", SceneAnimStop, &scn::title::Commander::SceneAnimStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void LocatorAnim(string)", LocatorAnim, &scn::title::Commander::LocatorAnim);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "Scn.Title.Chara Chara(int)", Chara, &scn::title::Commander::Chara);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void CompanyLogoAppear()", CompanyLogoAppear, &scn::title::Commander::CompanyLogoAppear);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void TitleInfoAppear()", TitleInfoAppear, &scn::title::Commander::TitleInfoAppear);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void TitleInfoEffect(int)", TitleInfoEffect, &scn::title::Commander::TitleInfoEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void TitleInfoEffectBG(int)", TitleInfoEffectBG, &scn::title::Commander::TitleInfoEffectBG);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void CinemaScopeOut()", CinemaScopeOut, &scn::title::Commander::CinemaScopeOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void CinemaScopeHide()", CinemaScopeHide, &scn::title::Commander::CinemaScopeHide);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void BGMStart()", BGMStart, &scn::title::Commander::BGMStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void SEStart(int)", SEStart, &scn::title::Commander::SEStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void SEStop()", SEStop, &scn::title::Commander::SEStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Title.Commander", "void BGSetFrameRate(float)", BGSetFrameRate, &scn::title::Commander::BGSetFrameRate);
}

}}  // namespace mintglue::Scn__Title__Commander
