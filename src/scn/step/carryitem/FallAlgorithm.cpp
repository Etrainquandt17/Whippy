#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/FallAlgorithm.h"

#include "gobj/FootState.h"
#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "ocoll/Attack.h"
#include "ocoll/AttackResult.h"
#include "ocoll/SearchHit.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/arena/Manager.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/IndiviUtil.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/Utility.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/Water.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/map/KindUtil.h"

namespace scn {
namespace step {
namespace carryitem {

namespace {

const common::FallParam& t_param(CarryItem& carryItem) {
    return carryItem.param().common().mFall;
}

// TODO: ocoll::AttackResultData has this member itself, at 0x18.
struct AttackResultData : public ::ocoll::AttackResultData {
    u64 mRootOwnerID;
};

}

FallAlgorithm::FallAlgorithm(CarryItem& carryItem)
    : mObj(carryItem)
    , mIsBounded(false)
    , mIsRotMinus(true)
    , mRotV(carryItem.model().rotCtrl().getRotV())
    , mRotH(carryItem.model().rotCtrl().getRotH() * mObj.target().getSign())
    , mRotSpeedRate(1.0f)
    , mBoundSE(0x101) {
    init();
}

FallAlgorithm::FallAlgorithm(CarryItem& carryItem, u32 boundSE)
    : mObj(carryItem)
    , mIsBounded(false)
    , mIsRotMinus(true)
    , mRotV(carryItem.model().rotCtrl().getRotV())
    , mRotH(carryItem.model().rotCtrl().getRotH() * mObj.target().getSign())
    , mRotSpeedRate(1.0f)
    , mBoundSE(boundSE) {
    init();
}

void FallAlgorithm::init() {
    if (mObj.isReputed() || mObj.move().velocity().y > 0.0f) {
        mObj.footState().setAir();
        setAttack();
    } else {
        mObj.footState().setGround();
        hel::math::Vector3 velocity = mObj.move().velocity();
        velocity.y -= 0.0001f;
        mObj.move().setVelocity(velocity);
    }
    mObj.objColl().setAttackType(static_cast<ocoll::AttackType>(0x247));
    if (mObj.move().velocity().y > 0.0f) {
        mObj.setIsEnableCarry(false);
    }
    mObj.vacuumReceiver().setIsValid(true);
    mObj.objColl().addSearchHit(0, 0.5f, hel::math::Vector2(0.0f, 0.5f));
    if (mObj.kind() == 2 && mObj.comp().arenaManager().isArena()) {
        if (map::KindUtil::IsArenaRoomMap(mObj.comp().context().mapKind)) {
            mObj.comp().arenaManager().setBoxState(static_cast<scn::arena::ArenaData::BoxState>(3));
        } else if (map::KindUtil::IsArenaBossMap(mObj.comp().context().mapKind)) {
            mObj.comp().arenaManager().setBoxState(static_cast<scn::arena::ArenaData::BoxState>(1));
        }
    }
}

FallAlgorithm::~FallAlgorithm() {
    mObj.vacuumReceiver().setIsValid(false);
    mObj.setIsEnableCarry(true);
    mObj.resetReleaseType();
    mObj.objColl().clearSearchHit();
}

void FallAlgorithm::procAnim() {
    f32 speed = mRotSpeedRate * (mObj.water().isInWater() ? t_param(mObj)._8 : t_param(mObj)._4);
    if (mObj.footState().isAir()) {
        if (mObj.getReleaseType() != RELEASE_TYPE_PUT) {
            if (0.0f < mObj.move().velocity().x) {
                mIsRotMinus = true;
            }
            if (mObj.move().velocity().x < 0.0f) {
                mIsRotMinus = false;
            }
            f32 add = speed * (mIsBounded ? t_param(mObj)._C : t_param(mObj)._10);
            mRotV += add * (mIsRotMinus ? -1.0f : 1.0f);
            if (!mIsBounded) {
                mRotH += speed * t_param(mObj)._14;
            }
        }
    } else {
        mRotV = 0.0f;
        mRotH += speed * t_param(mObj)._18;
    }
    if (360.0f <= mRotH) {
        mRotH -= 360.0f;
    }
    if (mRotH < 0.0f) {
        mRotH += 360.0f;
    }
    mObj.model().rotCtrl().initRotV(mRotV);
    mObj.model().rotCtrl().initRotH(mRotH);
}

void FallAlgorithm::procMove() {
    if (mObj.water().isInWater()) {
        f32 max = t_param(mObj)._1C;
        hel::math::Vector3 velocity = mObj.move().velocity();
        if (max < hel::math::Math::Abs(velocity.x)) {
            mObj.move().setSpeedH(max * static_cast<f32>(hel::math::Math::Sign(velocity.x)));
        }
        if (max < hel::math::Math::Abs(velocity.y)) {
            mObj.move().setSpeedV(max * static_cast<f32>(hel::math::Math::Sign(velocity.y)));
        }
    }
    gobj::MoveParamDecel decel = t_param(mObj)._20;
    gobj::MoveParamFall fall = t_param(mObj)._24;
    if (mObj.water().isInWater()) {
        decel = t_param(mObj)._30;
        fall = t_param(mObj)._34;
    }
    if (mObj.footState().isAir()) {
        mObj.move().airDecelFall(decel, fall);
    } else {
        mObj.move().groundDecel(decel);
    }
    if (mObj.move().velocity().y <= 0.0f) {
        mObj.setIsEnableCarry(true);
    }
}

void FallAlgorithm::procFixPos() {
    f32 rate = mObj.water().isInWater() ? t_param(mObj)._44 : t_param(mObj)._40;
    chara::MapCollResult result = mObj.mapColl().result();
    if (result.isHitFloor() && mObj.move().velocity().y <= 0.0f) {
        if (mObj.footState().isAir()) {
            if (mIsBounded || mObj.getReleaseType() == RELEASE_TYPE_PUT) {
                mObj.move().resetVelocity();
                mObj.footState().setGround();
                mObj.setReleaseType(RELEASE_TYPE_PUT);
            } else {
                obj().move().setSpeedV(rate * t_param(mObj)._4C);
                obj().move().setSpeedH(rate * (t_param(mObj)._48 * obj().move().velocity().x));
                mIsBounded = true;
            }
            if (Utility::InScreen(mObj, 3.0f)) {
                obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x9F), obj().location().pos());
                mObj.soundSE().start(mBoundSE);
            }
        }
        mObj.objColl().clearAttack();
    } else {
        if (mObj.footState().isGround()) {
            setAttack();
        }
        mObj.footState().setAir();
    }
    if (result.isHitWall()) {
        obj().move().setSpeedH(-1.0f * t_param(mObj)._50 * obj().move().velocity().x);
    }
    if (IndiviUtil::IsDeadOnDamageField(mObj) && (mObj.mapColl().result()._6 || mObj.mapColl().result()._7)) {
        mObj.deadWithEffect();
    }
}

void FallAlgorithm::procObjCollReact() {
    if (mObj.objColl().attack().isCollide() && IndiviUtil::IsReflectOnCollide(mObj.kind()) && isCollideBossOrEnemy()) {
        obj().move().setSpeedH(-1.0f * t_param(mObj)._50 * obj().move().velocity().x);
    }
    if (IndiviUtil::IsDeadByStrongEnemy(mObj)) {
        for (u32 i = 0; i < mObj.objColl().searchHit().getCollidedNum(); i++) {
            if (isBreakEnemy(mObj.objColl().searchHit().getCollidedHitOwnerRootUid(i))) {
                mObj.deadWithEffect();
                return;
            }
        }
        for (u32 i = 0; i < mObj.objColl().attack().result().dataNum(); i++) {
            u64 uid = static_cast<const AttackResultData&>(mObj.objColl().attack().result().getData(i)).mRootOwnerID;
            if (isBreakEnemy(uid)) {
                mObj.deadWithEffect();
                return;
            }
        }
    }
}

void FallAlgorithm::setRotH(f32 rotH) {
    mRotH = rotH;
}

void FallAlgorithm::setRotSpeedRate(f32 rate) {
    mRotSpeedRate = rate;
}

void FallAlgorithm::setIsBounded(bool isBounded) {
    mIsBounded = isBounded;
}

bool FallAlgorithm::isBreakEnemy(u64 uid) {
    util::ObjRefHandle<enemy::Enemy> enemy = mObj.comp().enemyManager().getEnemyByOCollOwnerUID(uid);
    if (enemy.isAlive()) {
        map::BinEnemyKind kind = enemy->kind();
        switch (kind) {
        case 0x60:
        case 0x61:
        case 0x26:
        case 0x38:
        case 0x5B:
        case 0x63:
            return true;
        }
    }
    return false;
}

bool FallAlgorithm::isCollideBossOrEnemy() {
    const ::ocoll::AttackResult& result = mObj.objColl().attack().result();
    if (!result.isCollide()) {
        return false;
    }
    for (u32 i = 0; i < result.dataNum(); i++) {
        u64 uid = result.getData(i).mOwnerID;
        util::ObjRefHandle<enemy::Enemy> enemy = mObj.comp().enemyManager().getEnemyByOCollOwnerUID(uid);
        bool isEnemy = false;
        if (enemy.isAlive()) {
            isEnemy = enemy->kind() != 0x64;
        }
        bool isBoss = mObj.comp().bossManager().getBossByObjCollOwnerID(uid).isAlive();
        if (isEnemy || isBoss) {
            return true;
        }
    }
    return false;
}

void FallAlgorithm::setAttack() {
    mObj.objColl().clearAttack();
    if (mObj.isCatched()) {
        obj().objColl().addAttack(0, t_param(mObj)._0, hel::math::Vector2(0.0f, 0.5f), hel::math::Vector2(0.0f, 0.5f), true);
        mObj.objColl().renewAttack();
    }
}

}}}  // namespace scn::step::carryitem
