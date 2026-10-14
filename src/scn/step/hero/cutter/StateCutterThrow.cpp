#include "scn/step/hero/cutter/StateCutterThrow.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/cutter/StateCutterSweepCutter.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace cutter {

bool StateCutterThrow::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCutterThrow, Hero*>(hero);
        return true;
    }
    return false;
}

StateCutterThrow::StateCutterThrow(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsHold(true) {
    obj().model().setFixDir(true);
    if (obj().footState().isGround()) {
        obj().model().script().start(0x92);
    } else {
        obj().model().script().start(0x94);
    }
    Utility::AirAttackInitSpeedV(obj());
}

StateCutterThrow::~StateCutterThrow() {
}

void StateCutterThrow::procAnim() {
    CutterParamThrow param = obj().param().cutter()._68;
    if (!obj().hid().isHold(0x20)) {
        mIsHold = false;
    }
    mFrame++;
    if (mFrame == param._0) {
        f32 sign = obj().model().isRightDir() ? 1.0f : -1.0f;
        Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
        Vector2 pos(heroPos.x, heroPos.y);
        pos.y += param._4;
        Vector2 weaponPos = pos;
        weaponPos.x += sign * param._8;
        Vector2 speed(param._C * sign, 0.0f);
        speed.x += obj().move().velocity().x;
        if (obj().hid().isHold(8)) {
            speed.y = param._10;
        }
        if (obj().hid().isHold(4)) {
            speed.y = -param._10;
        }
        weapon::Desc desc;
        desc.mKind = static_cast<weapon::Kind>(6);
        desc.mVariation = 0;
        desc.mFlag = static_cast<ostop::Flag>(1);
        desc.mPos = weaponPos;
        desc._14 = pos;
        desc._1c = speed;
        desc.mOwner = &obj().objColl().objColl().owner();
        obj().comp().weaponManager().request(desc);
        obj().model().weapon().setVisibility(false);
        if (mIsHold) {
            if (StateCutterSweepCutter::TryToChangeState(objPtr())) {
                return;
            }
        }
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCutterThrow::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateCutterThrow::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::cutter
