#include "scn/step/weapon/goliathenergyball/StateExplode.h"

#include "gobj/Move.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/Param.h"
#include "snd/SERequestor.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

StateExplode::StateExplode(Weapon* weapon)
    : StateBase(weapon)
    , mFrame(0)
    , mIsEffectRequested(false)
    , mAttacker(weapon->comp(), weapon->objColl().searchHit()) {
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    obj().move().resetVelocity();
}

void StateExplode::procAnim() {
    const Param& param = obj().param().goliathEnergyBall();
    mFrame++;
    if (mFrame == param._C) {
        reqEffect();
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(9));
        obj().soundSE().start(0x366);
        reqStar();
    }
    if (mFrame == param._10) {
        f32 bottom =
            static_cast<const Component&>(obj().comp()).mainCamera().getViewRect()._4 - obj().location().pos().y;
        f32 top = 7.0f + bottom;
        for (int i = 0; i < 3; i++) {
            f32 x = 2.0f * (1.75f * static_cast<f32>(i - 1));
            Vector2 start(x, bottom);
            Vector2 end(x, top);
            obj().objColl().addSearchHit(0, 1.75f, start, end);
        }
    }
    if (mFrame == param._14) {
        obj().dead();
    }
}

void StateExplode::procMove() {}

void StateExplode::procFixPos() {}

void StateExplode::procObjCollReact() {
    if (mAttacker.chkCaptureHero()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x23));
        mAttacker.clearCapture();
    }
}

void StateExplode::reqEffect() {
    mIsEffectRequested = true;
    const Param& param = obj().param().goliathEnergyBall();
    Vector3 pos = obj().location().pos();
    pos.y = param._18 + static_cast<const Component&>(obj().comp()).mainCamera().getViewRect()._4;
    Direction3 dir = Direction3::BASIS;
    dir.mFront = Vector3::BASIS_Y;
    dir.restructFrontLeft();
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x297), pos, 2.0f);
    for (int i = 0; i < 7; i++) {
        Vector3 effectPos = pos;
        effectPos.x += 1.6f * static_cast<f32>(i - 3);
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x298), effectPos, dir, 3.0f);
    }
}

void StateExplode::reqStar() {
    const Param& param = obj().param().goliathEnergyBall();
    Vector2 center = static_cast<const Component&>(obj().comp()).mainCamera().getViewRect().getCenter();
    Vector2 offset(param._24, 0.0f);
    Vector2 velocity(0.0f, -5.0f);
    Vector2 speed(param._1C, param._20);
    Utility::GenerateStarEffectFirstMapColl(
        obj(), center + offset, velocity, speed, static_cast<map::BinEnemyVariation>(0x19B), 0
    );
    offset.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffectFirstMapColl(
        obj(), center + offset, velocity, speed, static_cast<map::BinEnemyVariation>(0x19B), 0
    );
}

}}}}  // namespace scn::step::weapon::goliathenergyball
