#include "scn/step/weapon/tsukikageshuriken/StateMain.h"

#include "gobj/Anim.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/map/LandManager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/tsukikageshuriken/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace tsukikageshuriken {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mHitFrame(0), _10(0.0f), mIsHit(false) {
    const Param& param = obj().param().tsukikageshuriken();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19F));
    obj().objColl().addAttack(0, param._0);
    obj().objColl().addHit(0, param._4);
    hel::math::Direction3 dir1;
    hel::math::Direction3 dir2;
    hel::math::Matrix34 mtx;
    if (obj().target().isRightDir()) {
        dir1 = hel::math::Direction3(
            hel::math::Vector3(0.0f, 1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, -1.0f), hel::math::Vector3(1.0f, 0.0f, 0.0f)
        );
        dir2 = hel::math::Direction3(
            hel::math::Vector3(0.0f, 1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, 1.0f), hel::math::Vector3(-1.0f, 0.0f, 0.0f)
        );
        mtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3::BASIS_X, -90.0f);
    } else {
        dir1 = hel::math::Direction3(
            hel::math::Vector3(0.0f, -1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, 1.0f), hel::math::Vector3(1.0f, 0.0f, 0.0f)
        );
        dir2 = hel::math::Direction3(
            hel::math::Vector3(0.0f, -1.0f, 0.0f), hel::math::Vector3(0.0f, 0.0f, 1.0f), hel::math::Vector3(1.0f, 0.0f, 0.0f)
        );
        mtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3::BASIS_X, 90.0f);
    }
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x4A7), 0, dir1);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4A1), 0);
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x4A8), 0, dir2);
    obj().model().setCustomMtx(mtx);
    obj().model().reqScript(0);
    obj().landConstraint().setMode(static_cast<chara::LandConstraint::Mode>(3));
}

void StateMain::procMove() {
    obj().move().airAccelFall(!obj().target().isRightDir(), gobj::MoveParamAccel::Zero(), gobj::MoveParamFall::Zero());
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit() && !mIsHit) {
        obj().soundSE().start(0x2E3);
        obj().model().anim().setFrameRate(0.0f);
        obj().effect().normal().release();
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x62), 0, 0.6f);
        obj().mapColl().setValid(false);
        obj().move().resetVelocity();
        obj().objColl().clearAttack();
        obj().objColl().clearHit();
        mIsHit = true;
    }
    if (mIsHit) {
        mHitFrame++;
        hel::math::Vector3 pos = obj().location().pos();
        bool isExistLand = obj().comp().mapLandManager().native().isExistLand(hel::math::Vector2(pos.x, pos.y));
        if (mHitFrame == 30 || isExistLand) {
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), pos);
            obj().dead();
        }
    }
}

void StateMain::procObjCollReact() {
    mFrame++;
    if (!mIsHit) {
        if (mFrame == 250 || obj().objColl().hit().isCollide() || obj().objColl().attack().isCollideGimmick() ||
            obj().objColl().attack().isCollide()) {
            obj().effect().normal().release();
            hel::math::Vector3 pos = obj().location().pos();
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), pos);
            obj().dead();
        }
    }
}

}}}}  // namespace scn::step::weapon::tsukikageshuriken
