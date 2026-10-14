#include "scn/step/hero/cutter/StateCutterThrowLong.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjList.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace cutter {

StateCutterThrowLong::StateCutterThrowLong(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().model().setFixDir(true);
    obj().model().script().start(0x98);
    Vector3 scale = Vector3::ALL_ONE * obj().param().cutter()._7C;
    obj().model().model().nodes().at(4).localMtx().setScale(scale);
}

StateCutterThrowLong::~StateCutterThrowLong() {
    Vector3 scale = Vector3::ALL_ONE;
    obj().model().model().nodes().at(4).localMtx().setScale(scale);
}

void StateCutterThrowLong::procAnim() {
    const CutterParam& param = obj().param().cutter();
    mFrame++;
    if (mFrame == param._80._0) {
        f32 sign = obj().model().isRightDir() ? 1.0f : -1.0f;
        Vector3 heroPos = static_cast<const Hero&>(obj()).location().pos();
        Vector2 pos(heroPos.x, heroPos.y);
        pos.y += param._80._4;
        Vector2 weaponPos = pos;
        weaponPos.x += sign * param._80._8;
        Vector2 speed(param._80._C * sign, 0.0f);
        if (obj().hid().isHold(8)) {
            speed.y = param._80._10;
        }
        if (obj().hid().isHold(4)) {
            speed.y = -param._80._10;
        }
        weapon::Desc desc;
        desc.mKind = static_cast<weapon::Kind>(7);
        desc.mVariation = 0;
        desc.mFlag = static_cast<ostop::Flag>(1);
        desc.mPos = weaponPos;
        desc._14 = pos;
        desc._1c = speed;
        desc.mOwner = &obj().objColl().objColl().owner();
        obj().comp().weaponManager().request(desc);
        obj().model().weapon().setVisibility(false);
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCutterThrowLong::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateCutterThrowLong::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::cutter
