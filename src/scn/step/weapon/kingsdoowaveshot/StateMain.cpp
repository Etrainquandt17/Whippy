#include "scn/step/weapon/kingsdoowaveshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/kingsdoowaveshot/Param.h"
#include "std/cmath.h"

namespace scn {
namespace step {
namespace weapon {
namespace kingsdoowaveshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mIsStar(false) {
    const Param& param = obj().param().kingsDooWaveShot();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x2C), 0);
    obj().worldCage().setIsValid(true);
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseCenter(param._34, param._38, param._3C));
    obj().mapColl().setValid(true);
    hel::math::Vector3 velocity = obj().move().velocity();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1AF));
    switch (obj().variation()) {
    case 0:
    case 1: {
        mIsStar = true;
        f32 angle = 57.29578f * static_cast<f32>(acos(velocity.cos(hel::math::Vector3::BASIS_X * obj().target().getSign())));
        if (angle > param._14) {
            velocity *= param._C;
        } else {
            velocity *= param._10;
        }
        obj().objColl().addAttack(0, param.mAttackRadius);
        break;
    }
    case 2:
        mIsStar = false;
        velocity *= param._C;
        obj().objColl().addAttack(0, param.mAttackRadiusBig);
        obj().model().setBaseScale(hel::math::Vector3::ALL_ONE * param.mScaleBig);
        break;
    }
    obj().move().setVelocity(velocity);
}

void StateMain::procAnim() {
    const Param& param = obj().param().kingsDooWaveShot();
    mFrame++;
    if (mFrame >= param.mLifeFrame) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    const Param& param = obj().param().kingsDooWaveShot();
    if (obj().mapColl().isHit() || obj().worldCage().isCorrected()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x41), obj().location().pos());
        if (obj().variation() == 2) {
            obj().comp().permSoundSE().start(0x5AD);
        } else {
            obj().comp().permSoundSE().start(0x58A);
        }
        if (mIsStar) {
            hel::math::Vector2 offset(param.mStarOffset.x * obj().target().getSign(), param.mStarOffset.y);
            hel::math::Vector2 velocity = obj().variation() == 1
                ? hel::math::Vector2(param.mStarVelocity1.x * obj().target().getSign(), param.mStarVelocity1.y)
                : hel::math::Vector2(param.mStarVelocity.x * obj().target().getSign(), param.mStarVelocity.y);
            if (obj().mapColl().result().mIsHitRoof || (obj().worldCage().isCorrected() && obj().worldCage().getCorrectedDiff().y < 0.0f)) {
                velocity *= -1.0f;
            }
            Utility::GenerateStarEffect(obj(), offset, velocity, map::BinEnemyVariation_StarPuff);
            hel::math::Direction3 dir = obj().target().isRightDir() ? hel::math::Direction3::FRONT_TO_LEFT : hel::math::Direction3::FRONT_TO_RIGHT;
            obj().effect().normal().requestPD(static_cast<effect::Kind>(0xB4), obj().location().pos() + offset.toVector3(), dir);
        }
        obj().dead();
    }
}

}
}
}
}
