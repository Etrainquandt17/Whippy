#include "scn/step/hero/stone/Utility.h"
#include "g3d/ModelAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LogoutController.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/stone/Context.h"
#include "scn/step/hero/stone/GearNodeRandomChanger.h"
#include "scn/step/hero/stone/StateEnd.h"
#include "scn/step/map/KindUtil.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

void Utility::OnStateStartChange(Hero& hero, Context& context) {
    hero.model().body().model().changeParentNode(hero.model().body().defaultParentNodeIndex());
    InitRotH(hero, context);
    hero.objColl().setXlu();
    hero.water().setForbidChangeState(true);
    hero.nururi().setCanNururi(false);
    if (!map::KindUtil::IsFinalBattle(hero.comp().context().mapKind)) {
        hero::Utility::SetSecondMoveIsValid(hero, false);
        hero.landConstraint().resetMode();
    }
}

void Utility::OnStateEndChange(Hero& hero) {
    hero.model().body().model().removeParentNode();
    hero.objColl().unsetXlu();
    hero.water().setForbidChangeState(false);
    hero.move().resetMoveRate();
    hero::Utility::SetSecondMoveIsValid(hero, true);
}

void Utility::InitRotH(Hero& hero, Context& context) {
    if (hero.model().model().g3dModel().isVisible()) {
        hero.model().modelRotCtrl().initRotH(context.getRotAngle());
        return;
    }
    switch (context.nodeChanger().selectedIndex()) {
    case 0:
    case 1:
    case 2:
    case 12:
    case 13:
    case 9:
    case 10:
    case 6:
        hero.model().modelRotCtrl().initRotH(context.getRotAngle());
        break;
    default:
        hero.model().modelRotCtrl().initRotH(hero.param().stone()._0 + context.getRotAngle());
        hero.model().modelRotCtrl().setRotHIntpRate(hero.param().stone()._4);
        break;
    }
}

void Utility::UpdateSlipRolling(Hero& hero, Context& context) {
    if (context.isRotEnable()) {
        const StoneParam& param = hero.param().stone();
        u32 max = context.getMaxRotFrame();
        if (context.getRotFrame() < max) {
            f32 t = static_cast<f32>(context.getRotFrame()) / static_cast<f32>(max);
            f32 rate = 1.5f * t + t * (-0.5f * t * t);
            rate *= param._10;
            context.setRotAngle(rate);
            context.incRotFrame();
        } else {
            context.setRotAngle(0.0f);
        }
    }
    InitRotH(hero, context);
}

void Utility::ProcMoveChange(Hero& hero) {
    if (hero.water().isInWater()) {
        hero.move().setMoveRate(0.25f);
    } else {
        hero.move().resetMoveRate();
    }
}

void Utility::MoveGround(Hero& hero, Context& context) {
    if (context.isRun()) {
        hero.move().groundDecel(gobj::MoveParamDecel::Create(0.0018f));
    } else {
        hero::Utility::MoveDefaultBrake(hero);
    }
}

bool Utility::IsSlope(Hero& hero) {
    if (hero.footState().isGround()) {
        hel::math::Vector2 normal = hero.mapColl()._74;
        if (hel::math::Math::AbsF32(normal.x) > 0.1f) {
            return true;
        }
    }
    return false;
}

bool Utility::ChkCancel(Hero& hero) {
    if (hero.hid().isTrigger(0x20) || hero.logoutController().isLogoutForce()) {
        hero.stateChanger().setNextState<StateEnd, Hero*>(&hero);
        return true;
    }
    return false;
}

}
}
}
}
