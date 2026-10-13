#include "scn/step/hero/damage/Utility.h"
#include "app/Random.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

void Utility::InitTarget(Hero& hero) {
    if (hero.objColl().objColl().bodyColl().isCollide()) {
        hel::math::Vector2 attackPos = hero.objColl().objColl().bodyColl().damageInfo().data().mAttackPos;
        hero.target().setIsRightDir(hero.location().pos().x < attackPos.x);
    }
}

void Utility::InitVelocity(Hero& hero) {
    if (hero.objColl().objColl().bodyColl().isCollide()) {
        hel::math::Vector3 velocity = hel::math::Vector3::BASIS_X;
        const chara::DamageInfo& info = hero.objColl().objColl().bodyColl().damageInfo();
        f32 angle = info.data().mAngle;
        f32 width = info.data().mWidth;
        f32 speed = info.data().mSpeed;
        f32 rot = width * app::Random::RandAF() + angle;
        velocity.rotate(hel::math::Vector3::BASIS_Z, 0.017453292f * rot);
        velocity.x *= -1.0f * hero.target().getSign();
        velocity *= speed;
        hero.move().setVelocity(velocity);
    }
}

bool Utility::ReflectWallL(Hero& hero) {
    return ReflectWall(hero, hero.param().common()._47C);
}

bool Utility::ReflectWallS(Hero& hero) {
    return ReflectWall(hero, hero.param().common()._490);
}

bool Utility::ReflectWall(Hero& hero, const common::ParamReflectWall& param) {
    MapCollResult result = hero.mapColl().result();
    hel::geo::Rect rect = hero.comp().mainCamera().getViewRect();
    hel::math::Vector3 velocity = hero.move().velocity();
    hel::math::Vector3 pos = hero.location().pos();
    bool isReflect = false;
    if (result.mIsHitFloor) {
        hero.move().setSpeedV(-param._0 * velocity.y);
        isReflect = true;
    }
    if (result.mIsHitRoof) {
        hero.move().setSpeedV(-param._4 * velocity.y);
        isReflect = true;
    }
    if (result.isHitWall()) {
        hero.move().setSpeedH(-param._8 * velocity.x);
        isReflect = true;
    }
    if (pos.y > rect._0) {
        hero.move().setSpeedV(-param._C * velocity.y);
        isReflect = true;
    }
    if (pos.x < rect._8 || pos.x > rect._C) {
        hero.move().setSpeedH(-param._10 * velocity.x);
        isReflect = true;
    }
    return isReflect;
}

}
}
}
}
