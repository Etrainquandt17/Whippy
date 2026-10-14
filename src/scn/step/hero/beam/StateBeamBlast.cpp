#include "scn/step/hero/beam/StateBeamBlast.h"
#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/BeamParam.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"

using app::Random;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace beam {

bool StateBeamBlast::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        if (hero->stateChecker().isJumpStart()) {
            hero->move().setSpeedV(hero->param().common()._158);
        }
        hero->stateChanger().setNextState<StateBeamBlast, Hero*>(hero);
        return true;
    }
    return false;
}

StateBeamBlast::StateBeamBlast(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mWait(0)
    , mShotCount(0)
    , mIsRight(true) {
    obj().piggyback().unlinkAll();
    obj().model().setFixDir(true);
    obj().model().script().start(0xC1);
    Vector3 velocity = obj().move().velocity();
    velocity.y += obj().param().beam()._0;
    if (velocity.y < obj().param().beam()._8) {
        velocity.y = obj().param().beam()._8;
    }
    if (velocity.y > obj().param().beam()._4) {
        velocity.y = obj().param().beam()._4;
    }
    obj().move().setVelocity(velocity);
    const BeamParam& param = obj().param().beam();
    obj().invincible().set(param._C);
    mIsRight = obj().target().isRightDir();
    obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
}

StateBeamBlast::~StateBeamBlast() {
}

void StateBeamBlast::procAnim() {
    mFrame++;
    if (mFrame >= 10) {
        if (mWait != 0) {
            mWait--;
        } else {
            const f32 min = 25.0f;
            const f32 range = 25.0f;
            f32 angle = min + range * Random::RandNF();
            if (mShotCount == 0) {
                angle = 50.0f;
            } else if (mShotCount == 1) {
                angle = min;
            }
            Vector2 dir(0.0f, -1.0f);
            dir.rotate(0.017453292f * angle);
            dir.x *= mIsRight ? 1.0f : -1.0f;
            Vector2 pos = static_cast<const Hero&>(obj()).location().pos().getXY();
            pos.y += 0.6f;
            Vector2 weaponPos = pos;
            weaponPos += Vector2(mIsRight ? 0.5f : -0.5f, -0.25f);
            weapon::Desc desc;
            desc.mKind = static_cast<weapon::Kind>(0x16);
            desc.mVariation = 0;
            desc.mFlag = static_cast<ostop::Flag>(1);
            desc.mPos = weaponPos;
            desc._14 = pos;
            desc._1c = dir * 0.5f;
            desc.mOwner = &obj().objColl().objColl().owner();
            obj().comp().weaponManager().request(desc);
            mShotCount++;
            mWait = 4;
        }
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBeamBlast::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateBeamBlast::procFixPos() {
    if (obj().footState().isGround()) {
        if (common::StateRun::TryToChangeState(objPtr())
            || common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
            obj().model().modelRotCtrl().initRotV(0.0f);
        }
    }
}

}}}}  // namespace scn::step::hero::beam
