#include "scn/step/hero/super/Utility.h"
#include "gobj/Move.h"
#include "hid/RumbleRequestor.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/StageKind.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CaptureHeroReceiver.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/ItemCollReact.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SuperParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/info/HeroPanel.h"
#include "scn/step/map/KindUtil.h"
#include "scn/step/sfx/SuperBackPicture.h"
#include "scn/step/sfx/SuperFade.h"

namespace scn {
namespace step {
namespace hero {
namespace super {

void Utility::OnSuperActionStart(Hero& hero) {
    SetRenderFore(hero);
    hero.move().resetVelocity();
    hero.model().setFixDir(true);
    hero.runChecker().cancelContinue();
    SuperUseFuel(hero);
    hero.abilityManager().lockFuel();
    hero.objColl().setXlu();
    hero.captureHeroReceiver().setCanCapture(false);
    hero.water().setForbidChangeState(true);
    hero.itemCollReact().setForbidChangeAbility(true);
    hero.knockback().setIsValid(false);
    hero.landConstraint().setMode(static_cast<chara::LandConstraint::Mode>(0));
    hero::Utility::SetSecondMoveIsValid(hero, false);
    UnlinkPiggyBack(hero);
    hero.nururi().setCanNururi(false);
    hero.abilityManager().onSuperActionStart();
    hero.comp().superFade().setValid(true);
    hero.stateChecker().setIsForbidSpaceJump(true);
}

void Utility::OnSuperActionEnd(Hero& hero) {
    hero.comp().superBackPicture().releaseEffect();
    hero.comp().superBackPicture().releaseEffect2();
    hero.comp().superBackPicture().releaseEffectNonStop();
    hero.comp().superBackPicture().releaseEffectNonStop2();
    hero.abilityManager().onSuperActionEnd();
    hero::Utility::SetSecondMoveIsValid(hero, true);
    hero.itemCollReact().setForbidChangeAbility(false);
    hero.water().setForbidChangeState(false);
    hero.captureHeroReceiver().setCanCapture(true);
    hero.objColl().unsetXlu();
    hero.abilityManager().unlockFuel();
    UnsetRenderFore(hero);
    hero.abilityManager().incUseCount();
    hero.hidRumble().stop();
    hero.stateChecker().setIsForbidSpaceJump(false);
}

void Utility::SetRenderFore(Hero& hero) {
    hero.setRenderFore(true);
    hero.effect()._8.changeLayer(static_cast<core::DrawLayerKind>(8));
    hero.effect()._58.changeLayer(static_cast<core::DrawLayerKind>(8));
    hero.effect()._80.changeLayer(static_cast<core::DrawLayerKind>(8));
    hero.effect()._120.changeLayer(static_cast<core::DrawLayerKind>(8));
}

void Utility::UnsetRenderFore(Hero& hero) {
    hero.effect()._8.changeLayer(static_cast<core::DrawLayerKind>(6));
    hero.effect()._58.changeLayer(static_cast<core::DrawLayerKind>(6));
    hero.effect()._80.changeLayer(static_cast<core::DrawLayerKind>(6));
    hero.effect()._120.changeLayer(static_cast<core::DrawLayerKind>(5));
    hero.comp().superFade().setBack(false);
}

void Utility::InitFuel(Hero& hero) {
    // The original's is static and the link dropped it.
    const u32 max = 1000000;
    u32 fuel0 = static_cast<u32>(max * hero.param().super()._0);
    u32 fuel1 = static_cast<u32>(max * hero.param().super()._4);
    u32 fuel2 = static_cast<u32>(max * hero.param().super()._8);
    u32 fuel3 = static_cast<u32>(max * hero.param().super()._C);
    u32 fuel4 = static_cast<u32>(max * hero.param().super()._10);
    u32 fuel = fuel2;
    StageKind stage = map::KindUtil::ToStageKind(hero.comp().context().mapKind);
    switch (hero.abilityManager().abilityKind()) {
    case 0x19:
        switch (stage) {
        case 0:
            fuel = fuel0;
            break;
        case 8:
            fuel = fuel1;
            break;
        case 0x1A:
            fuel = fuel2;
            break;
        case 0x23:
            fuel = fuel4;
            break;
        case 0x26:
            fuel = fuel2;
            break;
        }
        break;
    case 0x1A:
        switch (stage) {
        case 3:
            fuel = fuel0;
            break;
        case 0xC:
            fuel = fuel2;
            break;
        case 0x1B:
            fuel = fuel2;
            break;
        case 0x26:
            fuel = fuel2;
            break;
        }
        break;
    case 0x1B:
        switch (stage) {
        case 6:
            fuel = fuel1;
            break;
        case 0x16:
            fuel = fuel2;
            break;
        case 0x1D:
            fuel = fuel2;
            break;
        case 0x26:
            fuel = fuel2;
            break;
        }
        break;
    case 0x1C:
        switch (stage) {
        case 0x10:
            fuel = fuel2;
            break;
        case 0x18:
            fuel = fuel2;
            break;
        case 0x22:
            fuel = fuel3;
            break;
        case 0x26:
            fuel = fuel2;
            break;
        }
        break;
    case 0x1D:
        switch (stage) {
        case 0xA:
            fuel = fuel2;
            break;
        case 0x12:
            fuel = fuel2;
            break;
        case 0x21:
            fuel = fuel2;
            break;
        case 0x26:
            fuel = fuel2;
            break;
        }
        break;
    }
    hero.comp().context();
    hero.abilityManager().initFuel(fuel);
}

void Utility::SuperUseFuel(Hero& hero) {
    const SuperParamAbility& param = Param(hero);
    hero.abilityManager().decFuel(param._0);
}

void Utility::SuperLeakFuel(Hero& hero) {
    if (hero.abilityManager().isStarted()) {
        hero.abilityManager().decFuel(CalcSuperLeakFuel(hero));
    }
}

u32 Utility::CalcSuperLeakFuel(Hero& hero) {
    f32 rate = Param(hero)._4;
    u32 count = hero.abilityManager().getUseCount();
    if (count > 0x13) {
        count = 0x13;
    }
    return static_cast<u32>(rate * hero.param().super()._14[count]);
}

void Utility::UnlinkPiggyBack(Hero& hero) {
    switch (hero.abilityManager().abilityKind()) {
    case 0x1B:
    case 0x1C:
    case 0x1D:
        hero.piggyback().unlinkAll();
        break;
    }
}

const SuperParamAbility& Utility::Param(Hero& hero) {
    switch (hero.abilityManager().abilityKind()) {
    case 0x19:
        return hero.param().super()._64[0];
    case 0x1A:
        return hero.param().super()._64[1];
    case 0x1B:
        return hero.param().super()._64[2];
    case 0x1C:
        return hero.param().super()._64[3];
    case 0x1D:
        return hero.param().super()._64[4];
    default:
        return hero.param().super()._64[0];
    }
}

void Utility::OnShowHero(Hero& hero) {
    hero.effect()._120.requestN(static_cast<effect::Kind>(0x5B3), 2);
    hero.infoHeroPanel().spGaugeFadeIn();
}

void Utility::OnHideHero(Hero& hero) {
    hero.effect()._120.releaseAndVanish();
    hero.infoHeroPanel().spGaugeFadeOut();
}

}}}}  // namespace scn::step::hero::super
