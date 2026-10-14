#include "scn/step/carryitem/repairparts/StateRepairThrow.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/Color.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/core/SceneChanger.h"
#include "scn/step/sfx/ScreenFade.h"

using hel::common::Color;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace carryitem {
namespace repairparts {

StateRepairThrow::StateRepairThrow(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFrame(0) {
    obj().model().rotCtrl().initRotH(90.0f);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().reqScript(0);
}

StateRepairThrow::~StateRepairThrow() {}

void StateRepairThrow::procAnim() {
    mFrame++;
    if (mFrame == obj().param().repairparts()._1C) {
        obj().soundSE().start(0x14B);
        Vector3 pos = obj().location().pos();
        pos.y += 1.0f;
        obj().effect().requestP(static_cast<effect::Kind>(0x33F), pos);
    }
    if (mFrame == obj().param().repairparts()._20) {
        obj().comp().screenFade().setColor(Color(0xFF, 0xFF, 0xFF, 0xFF));
        obj().comp().screenFade().setFadeOut(obj().param().repairparts()._24);
    }
    if (mFrame >= obj().param().repairparts()._20 + obj().param().repairparts()._24 + 5) {
        obj().dead();
        obj().comp().sceneChanger().changeShipRepairDemoMovie();
    }
}

void StateRepairThrow::procMove() {
    if (mFrame < obj().param().repairparts()._1C) {
        obj().move().airDecelFall(
            gobj::MoveParamDecel::Create(obj().param().repairparts()._C),
            gobj::MoveParamFall::Create(
                obj().param().repairparts()._14, obj().param().repairparts()._10, obj().param().repairparts()._18));
    }
}

void StateRepairThrow::procFixPos() {}

}}}}  // namespace scn::step::carryitem::repairparts
