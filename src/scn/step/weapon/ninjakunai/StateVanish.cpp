#include "scn/step/weapon/ninjakunai/StateVanish.h"

#include "app/Random.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjakunai/Utility.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

StateVanish::StateVanish(Weapon* weapon, VanishKind kind) : StateBase(weapon), mFrame(0) {
    f32 rot = obj().param().ninjaKunai()._84;
    f32 rotSign = obj().target().getSign();
    mRot = rotSign * rot;
    mKind = kind;
    mRotSign = 1.0f;
    obj().mapColl().setValid(false);
    obj().objColl().clearAttack();
    mRotSign = app::Random::Rand(2) == 0 ? 1.0f : -1.0f;
    f32 speedX = param()._0;
    f32 speedY = param()._4;
    if (isRoll()) {
        speedX += app::Random::RandF32(-param()._8, param()._8);
        speedY += app::Random::RandF32(-param()._C, param()._C);
    }
    f32 sign = obj().target().getSign();
    obj().move().setVelocity(hel::math::Vector3(speedX * sign, speedY, 0.0f));
}

StateVanish::~StateVanish() {}

void StateVanish::procAnim() {
    mFrame++;
    if (mFrame >= param()._24) {
        obj().dead();
    } else {
        Utility::Rotate(obj());
        mRot += mRotSign * param()._10;
        obj().model().rotCtrl().setRotV(mRot);
    }
}

void StateVanish::procMove() {
    obj().move().airDecelFall(param()._14, param()._18);
}

void StateVanish::procFixPos() {}

void StateVanish::procObjCollReact() {}

bool StateVanish::isRoll() const {
    return static_cast<u32>(mKind - VANISH_KIND_DROP_ROLL) <= 1;
}

const Param::Vanish& StateVanish::param() const {
    switch (mKind) {
    case VANISH_KIND_DROP:
    case VANISH_KIND_DROP_ROLL:
        return obj().param().ninjaKunai()._2C;
    case VANISH_KIND_REPEL_ROLL:
        return obj().param().ninjaKunai()._54;
    default:
        return obj().param().ninjaKunai()._2C;
    }
}

}}}}  // namespace scn::step::weapon::ninjakunai
