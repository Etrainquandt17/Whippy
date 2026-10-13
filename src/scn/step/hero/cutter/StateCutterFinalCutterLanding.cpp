#include "scn/step/hero/cutter/StateCutterFinalCutterLanding.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

StateCutterFinalCutterLanding::StateCutterFinalCutterLanding(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().script().start(0x91);
    obj().invincible().setPerm();
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().soundSE()._4.start(0x14F);
    hel::math::Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
    hel::math::Vector2 pos(heroPos.x, heroPos.y);
    pos.y += 0.15f;
    hel::math::Vector2 weaponPos = pos;
    pos.x += 0.2f * obj().target().getSign();
    hel::math::Vector2 speed(0.6f * obj().target().getSign(), 0.0f);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(8);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(1);
    desc.mPos = weaponPos;
    desc._14 = weaponPos;
    desc._1c = speed;
    desc.mOwner = &obj().objColl().objColl().owner();
    obj().comp().weaponManager().request(desc);
}

StateCutterFinalCutterLanding::~StateCutterFinalCutterLanding() {
}

void StateCutterFinalCutterLanding::procAnim() {
    mFrame++;
    if (mFrame >= 0x1A) {
        obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
    }
}

void StateCutterFinalCutterLanding::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateCutterFinalCutterLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        // &obj() and not objPtr(): the original link kept this function apart from
        // common::StateGuard::procFixPos, which has the same code, so the two call something different.
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}
}
}
}
