#include "scn/step/hero/beam/StateBeamWaveShot.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/BeamParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

StateBeamWaveShot::StateBeamWaveShot(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsRight(true) {
    obj().model().setFixDir(true);
    obj().model().script().start(0xC3);
    const BeamParam& param = obj().param().beam();
    obj().invincible().set(param._28);
    mIsRight = obj().target().isRightDir();
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(3));
}

StateBeamWaveShot::~StateBeamWaveShot() {
}

void StateBeamWaveShot::procAnim() {
    mFrame++;
    if (mFrame == obj().param().beam()._2C) {
        obj().move().resetSpeedV();
        obj().move().setSpeedH(obj().target().getSign() * obj().param().beam()._30);
        hel::math::Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY();
        pos.y += 0.6f;
        hel::math::Vector2 weaponPos = pos;
        hel::math::Vector2 speed(obj().param().beam()._34 * obj().target().getSign(), 0.0f);
        weapon::Desc desc;
        desc.mKind = static_cast<weapon::Kind>(0x17);
        desc.mVariation = 0;
        desc.mFlag = static_cast<ostop::Flag>(1);
        desc.mPos = weaponPos;
        desc._14 = pos;
        desc._1c = speed;
        desc.mOwner = &obj().objColl().objColl().owner();
        desc._2e = true;
        desc._2f = true;
        desc._30 = 5;
        obj().comp().weaponManager().request(desc);
        obj().soundSE()._78.stop();
        obj().abilityManager().resetCustomDarknessLightSizeKind();
        obj().effect()._58.release();
    }
    if (obj().model().isAllEnd()) {
        obj().model().anim().start(0, false, 0.0f);
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBeamWaveShot::procMove() {
    gobj::MoveParamDecel decel = obj().param().beam()._38;
    gobj::MoveParamFall fall = obj().param().beam()._3C;
    if (obj().footState().isGround()) {
        obj().move().groundDecel(decel);
    } else {
        obj().move().airDecelFall(decel, fall);
    }
}

void StateBeamWaveShot::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::beam
