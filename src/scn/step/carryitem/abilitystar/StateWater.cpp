extern "C" double fmod(double, double);

#include "scn/step/carryitem/abilitystar/StateWater.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Lifetime.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Water.h"

using hel::common::Color;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

// TODO: dropped by the link (0x78 bytes), so its code is not known. The angle it starts from is left out: the
// constant it used was dropped with it, and 0.0f here would put the unit's constants in another order.
StateWater::StateWater(CarryItem* carryItem)
    : StateBase(carryItem)
    , mRotSign(1.0f)
    , _10(false)
    , _14(0)
    , mFlashAngle(0.0f) {
    construct();
}

StateWater::StateWater(CarryItem* carryItem, f32 rot)
    : StateBase(carryItem)
    , mRot(rot)
    , mRotSign(1.0f)
    , _10(false)
    , _14(0)
    , mFlashAngle(0.0f) {
    construct();
}

StateWater::~StateWater() {}

void StateWater::procAnim() {
    if (!obj().water().isInWater() && obj().move().velocity().y > 0.0f) {
        obj().move().setSpeedV(0.0f);
    }
    mRot += 2.0f * mRotSign;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    if (obj().lifetime().get() <= obj().param().abilityStar()._44) {
        f32 t = static_cast<f32>(obj().lifetime().get()) / 180.0f;
        mFlashAngle += 60.0f * (1.0f - t);
        mFlashAngle = fmod(mFlashAngle, 360.0);
        f32 cos = Math::CosDegF(mFlashAngle);
        u8 alpha = static_cast<u8>(192.0f * (0.5f * (1.0f - cos)));
        obj().flash().set(Color(0xFF, 0xFF, 0xFF, alpha));
    }
    Matrix34 mtx = Matrix34::CreateRotAxisDeg(Vector3::BASIS_X, mRot);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

void StateWater::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().abilityStar()._58);
}

void StateWater::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    bool isDamage = result._6 || result._7;
    if (isDamage) {
        obj().deadWithEffect();
    }
}

void StateWater::construct() {
    obj().model().rotCtrl().initRotH(90.0f);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().reqScript(0);
    int sign = obj().move().velocity().x < 0.0f ? -1 : 1;
    mRotSign = static_cast<f32>(sign);
    obj().move().setMoveRate(0.15f);
    obj().vacuumReceiver().setIsValid(false);
    obj().setIsEnableCarry(false);
    obj().setCanGather(false);
    const Param& param = obj().param().abilityStar();
    obj().lifetime().set(param._54);
}

}}}}  // namespace scn::step::carryitem::abilitystar
