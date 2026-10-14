#include "scn/step/enemy/barracu/Custom.h"

#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "mcoll/detail/DetectArg.h"
#include "mcoll/detail/DetectResult.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/debug/GeneralDrawer.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/barracu/ParamData.h"
#include "scn/step/enemy/barracu/StateBound.h"
#include "scn/step/enemy/barracu/StateEscape.h"
#include "scn/step/enemy/barracu/StatePursuit.h"
#include "scn/step/enemy/barracu/StateSwimStraight.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/map/LandManager.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mAttacker(enemy.comp(), enemy.objColl().searchHit()), mIsHitMap(false), mFlashFrame(0) {
    mAttacker.setConstraintPos(enemy.location().pos());
}

bool Custom::onInit() {
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(1, 0.5f, Vector2(0.35f, 0.0f), Vector2(-0.35f, 0.0f));
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2f6);
    switch (obj().variation()) {
    case 0xa7:
        obj().stateChanger().setNextState<StateSwimStraight, Enemy*>(&obj());
        break;
    case 0xa8:
        obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
        break;
    }
    return true;
}

bool Custom::onOutWater() {
    obj().soundSE().start(0x2f6);
    obj().move().setSpeedV(0.1f);
    obj().stateChanger().setNextState<StateBound, Enemy*>(&obj());
    return true;
}

bool Custom::onHitPointIsZero() {
    releaseCaptureHero();
    return false;
}

bool Custom::onVacuumReceive() {
    releaseCaptureHero();
    return false;
}

bool Custom::onDamaged() {
    return isCaptureHero();
}

void Custom::onDead() {
    releaseCaptureHero();
}

void Custom::onCaptured() {
    releaseCaptureHero();
}

void Custom::onProcFixPos() {
    Vector3 pos = obj().model().model().nodes().at(2).worldMtx().getT();
    pos.y -= 0.5f;
    mAttacker.setConstraintPos(pos);
    if (mAttacker.isCapture()) {
        mfMapCheck();
        if (mFlashFrame != 0) {
            mFlashFrame--;
            if (mFlashFrame == 0) {
                mAttacker.heroObj()->damageFlash().unset();
            }
        }
        if (mIsHitMap) {
            mIsHitMap = false;
            setDamageCaptureHero(obj().param().barracu().mAttackDamage, false);
            vomitCaptureHero();
            obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
            obj().stateChanger().changeStateIfPossible();
        }
    }
}

bool Custom::isCaptureHero() {
    return mAttacker.isCapture();
}

bool Custom::chkCaptureHero() {
    if (mAttacker.chkCaptureHero()) {
        mAttacker.reqChangeState(hero::CAPTURE_HERO_STATE_KIND_F);
        mAttacker.heroObj()->location().setPos(obj().location().pos());
        mAttacker.heroObj()->mapColl().reset();
        mAttacker.heroObj()->mapColl().setValid(false);
        return true;
    }
    return false;
}

void Custom::vomitCaptureHero() {
    if (mAttacker.isCapture()) {
        mAttacker.heroObj()->damageFlash().unset();
        mAttacker.heroObj()->mapColl().setValid(true);
        mAttacker.heroObj()->move().setVelocity(Vector3(obj().target().getSign(), 0.225f, 0.0f));
        mAttacker.reqChangeState(hero::CAPTURE_HERO_STATE_KIND_10);
        mAttacker.clearCapture();
        mIsHitMap = false;
    }
}

void Custom::releaseCaptureHero() {
    if (mAttacker.isCapture()) {
        Vector2 velocity(0.0f, 0.1f);
        mAttacker.heroObj()->damageFlash().unset();
        mAttacker.heroObj()->mapColl().setValid(true);
        mAttacker.heroObj()->move().setVelocity(velocity.toVector3());
        mAttacker.reqChangeState(hero::CAPTURE_HERO_STATE_KIND_10);
        mAttacker.heroObj()->invincible().set(120);
        mAttacker.clearCapture();
    }
}

void Custom::setDamageCaptureHero(u32 damage, bool isCritical) {
    if (isCritical) {
        mAttacker.reqDamageCritical(damage);
    } else {
        mAttacker.reqDamage(damage);
    }
    if (mAttacker.isCapture()) {
        mAttacker.heroObj()->damageFlash().set(ocoll::ELEMENT_0);
        mFlashFrame = 20;
    }
}

bool Custom::chkReleaseHero() {
    if (!mAttacker.isCapture()) {
        return true;
    }
    return mAttacker.getResistPower() > 40;
}

void Custom::enableResistCaptureHero() {
    if (mAttacker.isCapture()) {
        mAttacker.enableResist(true);
    }
}

void Custom::disableResistCaptureHero() {
    if (mAttacker.isCapture()) {
        mAttacker.disableResist(true);
    }
}

void Custom::setSuccessCaptureHero() {
    if (mAttacker.isCapture()) {
        mAttacker.setSuccess();
    }
}

bool Custom::mfMapCheckPoint(Vector2 pos, Vector2 offset) {
    bool result = false;
    mcoll::detail::DetectArg arg;
    arg.setVelocity(offset);
    arg.setMoveRetryCountToZeroTime();
    arg.setIsPassThroughLand(false);
    arg.setIsGenerateFloorToOneSpaceGrid(false);
    arg.setIsGenerateFloorToTwoSpaceGrid(false);
    arg.setIsPassInvisibleLand(true);
    arg.setIsPassInvisibleWater(true);
    arg.setIsGroundMode(false);
    arg.setIsPassCrystalWallLand(false);
    arg.setIsPassDamageLand(true);
    arg.setIsAfterMoveDetect(false);
    mcoll::detail::DetectResult detect = obj().comp().mapLandManager().native().rayCheck(pos, arg);
    if (detect.collidedLogCount() == 1 && detect.collidedLog(0).isValid() && detect.collidedLog(0).info().isValid()) {
        result = true;
    }
    return result;
}

void Custom::mfMapCheck() {
    const ParamData& param = obj().param().barracu();
    Vector2 pos = obj().model().model().nodes().at(1).worldMtx().getT().getXY();
    Vector2 offset(param.mMapCheckX * obj().target().getSign(), param.mMapCheckY);
    mIsHitMap = mfMapCheckPoint(pos, offset);
    GXColor red = { 0xFF, 0x00, 0x00, 0xFF };
    obj().comp().debugGeneralDrawer().addPoint(pos, red);
    GXColor blue = { 0x00, 0x00, 0xFF, 0xFF };
    obj().comp().debugGeneralDrawer().addPoint(pos + offset, blue);
    if (!mIsHitMap) {
        pos = obj().model().model().nodes().at(1).worldMtx().getT().getXY();
        offset = Vector2(param.mMapCheckX * obj().target().getSign(), -param.mMapCheckY);
        mIsHitMap = mfMapCheckPoint(pos, offset);
        GXColor blue2 = { 0x00, 0x00, 0xFF, 0xFF };
        obj().comp().debugGeneralDrawer().addPoint(pos + offset, blue2);
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::barracu
