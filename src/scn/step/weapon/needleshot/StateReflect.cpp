#include "scn/step/weapon/needleshot/StateReflect.h"

#include "app/Random.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/needleshot/Param.h"

using app::Random;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateReflect::StateReflect(Weapon* weapon)
    : StateBase(weapon), mFrame(0), mRot(obj().model().rotCtrl().getRotV()), mRotSign(1.0f) {
    obj().mapColl().setValid(false);
    obj().objColl().clearAttack();
    mRotSign = Random::Rand(2) == 0 ? 1.0f : -1.0f;
    const Param& param = obj().param().needleShot();
    f32 speedX = param._24;
    f32 speedY = param._28;
    speedX += Random::RandF32(-param._2C, param._2C);
    speedY += Random::RandF32(-param._30, param._30);
    f32 sign = obj().move().velocity().x >= 0.0f ? 1.0f : -1.0f;
    Vector3 velocity(speedX * sign, speedY, 0.0f);
    obj().move().setVelocity(velocity);
    Vector3 scale = Vector3::ALL_ONE * param._20;
    obj().model().setScale(scale);
}

StateReflect::~StateReflect() {}

void StateReflect::procAnim() {
    const Param& param = obj().param().needleShot();
    mFrame++;
    if (mFrame >= param._48) {
        obj().dead();
    } else {
        mRot += mRotSign * param._34;
        obj().model().rotCtrl().setRotV(mRot);
    }
}

void StateReflect::procMove() {
    const Param& param = obj().param().needleShot();
    obj().move().airDecelFall(param._38, param._3C);
}

}}}}  // namespace scn::step::weapon::needleshot
