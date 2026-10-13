#include "scn/step/enemy/aquarock/StateMove.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "gobj/FootState.h"
#include "mcoll/LandManager.h"
#include "mcoll/detail/DetectArg.h"
#include "mcoll/detail/DetectResult.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/aquarock/Custom.h"
#include "scn/step/enemy/aquarock/ParamData.h"
#include "scn/step/map/LandManager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

struct NewDir {
    u32 mDirType;
    f32 mRot;
};

extern const NewDir newDirTbl[8][8] = {
    { { 2, 0.0f }, { 3, 0.0f }, { 6, 1.0f }, { 8, -1.0f }, { 2, 0.0f }, { 4, 1.0f }, { 2, 0.0f }, { 5, -1.0f } },
    { { 2, 0.0f }, { 3, 0.0f }, { 7, -1.0f }, { 9, 1.0f }, { 4, -1.0f }, { 3, 0.0f }, { 5, 1.0f }, { 3, 0.0f } },
    { { 6, -1.0f }, { 7, 1.0f }, { 4, 0.0f }, { 5, 0.0f }, { 4, 0.0f }, { 4, 0.0f }, { 2, -1.0f }, { 3, 1.0f } },
    { { 8, 1.0f }, { 9, -1.0f }, { 4, 0.0f }, { 5, 0.0f }, { 2, 1.0f }, { 3, -1.0f }, { 5, 0.0f }, { 5, 0.0f } },
    { { 6, 0.0f }, { 7, 1.0f }, { 6, 0.0f }, { 8, -1.0f }, { 6, 0.0f }, { 4, 1.0f }, { 2, -1.0f }, { 9, 0.0f } },
    { { 6, -1.0f }, { 7, 0.0f }, { 7, 0.0f }, { 9, 1.0f }, { 4, -1.0f }, { 7, 0.0f }, { 8, 0.0f }, { 3, 1.0f } },
    { { 8, 0.0f }, { 9, -1.0f }, { 6, 1.0f }, { 8, 0.0f }, { 2, 1.0f }, { 7, 0.0f }, { 8, 0.0f }, { 5, -1.0f } },
    { { 8, 1.0f }, { 9, 0.0f }, { 7, -1.0f }, { 9, 0.0f }, { 6, 0.0f }, { 3, -1.0f }, { 5, 1.0f }, { 9, 0.0f } },
};

extern const u32 dirTypeMapTbl[36] = {
    4, 6, 6, 6, 6, 6, 6, 6, 6, 2, 8, 8, 8, 8, 8, 8, 8, 8, 5, 9, 9, 9, 9, 9, 9, 9, 9, 3, 7, 7, 7, 7, 7, 7, 7, 7,
};

extern const u32 dirTypeNururiTbl[8] = {
    4, 6, 2, 8, 5, 9, 3, 7,
};

StateMove::StateMove(Enemy* enemy)
    : StateBase(enemy)
    , _8(0)
    , _c(false)
    , mPos(obj().location().pos())
    , mPrevPos(obj().location().pos())
    , mSpeed(0.0f)
    , mRot(0.0f)
    , mRotSpeed(0.0f)
    , _34(0.0f)
    , mDirType(obj().dirType())
    , _3c(false)
    , _40(obj().param().aquarock()._38)
    , mShakeFrame(0)
    , mIsShake(false) {
    f32 radius = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getRadius();
    obj().model().rotCtrl().setValid(false);
    obj().footState().setAir();
    obj().vacuumReceiver().setIsValid(false);
    obj().captureReceiver().setCanCapture(false);
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(2, -0.3f + radius);
    obj().objColl().bodyColl().setStateHitOnly();
    obj().objColl().clearAttack();
    obj().objColl().addAttack(0, 2, -0.3f + radius);
    obj().objColl().setAttackCenter(2, hel::math::Vector2(0.0f, 0.0f));
    obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x23D));
    f32 speed = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getSpeed();
    f32 r = radius / 2.0f;
    obj().objColl().addAttack(1, 2, r, hel::math::Vector2(0.0f, r + speed));
    obj().objColl().addAttack(1, 2, r, hel::math::Vector2(0.0f, -r - speed));
    obj().objColl().addAttack(1, 2, r, hel::math::Vector2(r + speed, 0.0f));
    obj().objColl().addAttack(1, 2, r, hel::math::Vector2(-r - speed, 0.0f));
    obj().objColl().setAttackType(1, static_cast<ocoll::AttackType>(0x233));
    obj().mapColl().setValid(false);
    mSpeed = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getSpeed();
    mRotSpeed = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getAngleSpeed();
    hel::math::Vector3 toCenter = hel::math::Vector3::BASIS_Y * radius - hel::math::Vector3(0.0f, 0.5f, 0.0f);
    obj().location().setToCenter(toCenter);
}

StateMove::~StateMove() {
    obj().soundSEState().stop();
}

void StateMove::procAnim() {
    if (!mIsShake) {
        mRot = mfCheckRotate(mRot + mRotSpeed);
        if (obj().kind() == 0x47) {
            _34 = mfCheckRotate(_34 - obj().param().aquarock()._18);
        }
        mfSetModelRotate();
    }
    if (!_c) {
        mfReqBubbleEffect();
    }
}

void StateMove::procMove() {
    if (_3c) {
        _3c = false;
        mPos = mPrevPos;
    } else {
        mPrevPos = mPos;
    }
    f32 rot = mfGetRotByDirType(mDirType);
    mPos = obj().location().pos();
    if (!mIsShake) {
        mPos.x += mSpeed * hel::math::Math::SinDegF(rot);
        mPos.y += mSpeed * hel::math::Math::CosDegF(rot);
    } else {
        mfShake();
        if (++mShakeFrame == obj().param().aquarock().mShakeFrame) {
            mIsShake = false;
            mShakeFrame = 0;
            obj().model().resetViewOffset();
        }
    }
    obj().location().setPos(mPos);
}

void StateMove::procFixPos() {
    f32 margin = obj().param().aquarock()._28;
    hel::geo::Rect rect = obj().comp().mainCamera().getWorldRect();
    if (obj().location().pos().x < rect._8 - margin || obj().location().pos().x > rect._C + margin ||
        obj().location().pos().y > rect._0 + margin || obj().location().pos().y < rect._4 - 2.0f * margin) {
        obj().soundSEState().stop();
        obj().dead();
        return;
    }
    hel::math::Vector2 center = obj().comp().mainCamera().getCenter();
    f32 height = 0.5f * obj().param().aquarock()._20 + obj().param().aquarock()._24;
    f32 width =
        0.5f * obj().param().aquarock()._20 * obj().comp().mainCamera().getAspect() + obj().param().aquarock()._24;
    hel::math::Vector2 diff = center - obj().location().centerPos().getXY();
    if (height < hel::math::Math::AbsF32(diff.y) || width < hel::math::Math::AbsF32(diff.x)) {
        if (!_c) {
            obj().soundSEState().stop();
            _c = true;
        }
    } else if (_c == true) {
        _8 = 0;
        _c = false;
    }
    if (!_c) {
        if (_8 % 0x80 == 0) {
            obj().soundSEState().start(0x51D);
            if (_8 == 0x80) {
                _8 = 0;
            }
        }
    }
    mfSetModelVisible();
    _8++;
    mfMapCheck();
}

void StateMove::mfReqBubbleEffect() {
    hel::math::Vector2 mapPos = obj().location().pos().getXY();
    if (obj().comp().mapLandManager().native().isWaterGrid(mapPos)) {
        if (--_40 == 0) {
            int rand = app::Random::Rand(3);
            hel::math::Vector3 pos = obj().model().model().nodes().at(2).worldMtx().getT();
            f32 rate;
            f32 rot = mfGetRotByDirType(mDirType);
            mfGetRotByDirType(mDirType);
            switch (obj().level()) {
            case 0:
                rate = 1.0f;
                break;
            case 1:
                rate = 0.75f;
                break;
            default:
                rate = 0.5f;
                break;
            }
            switch (rand) {
            case 1:
                rot += 45.0f;
                break;
            case 2:
                rot -= 45.0f;
                break;
            }
            switch (obj().variation()) {
            case 0xB1:
            case 0xC3:
            case 0xE2:
            case 0xE5:
                pos.x += -rate * hel::math::Math::SinDegF(rot) * obj().param().aquarock()._2c;
                pos.y += -rate * hel::math::Math::CosDegF(rot) * obj().param().aquarock()._2c;
                break;
            case 0xB2:
            case 0xC4:
            case 0xE3:
            case 0xE6:
                pos.x += -rate * hel::math::Math::SinDegF(rot) * obj().param().aquarock()._30;
                pos.y += -rate * hel::math::Math::CosDegF(rot) * obj().param().aquarock()._30;
                break;
            default:
                pos.x += -rate * hel::math::Math::SinDegF(rot) * obj().param().aquarock()._34;
                pos.y += -rate * hel::math::Math::CosDegF(rot) * obj().param().aquarock()._34;
                break;
            }
            obj().effect().state().requestP(static_cast<effect::Kind>(0x1FA), pos);
            _40 = obj().param().aquarock()._38;
        }
    }
}

void StateMove::mfSetModelRotate() {
    hel::math::Matrix34 mtx;
    mtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, 1.0f), mRot);
    obj().model().model().nodes().at(2).localMtx().setRTMtx(mtx);
    if (obj().kind() == 0x47) {
        mtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, 1.0f), _34);
        obj().model().model().nodes().at(3).localMtx().setRTMtx(mtx);
    }
}

void StateMove::mfShake() {
    f32 radius = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getRadius();
    hel::math::Vector3 offset(0.0f, 0.0f, 0.0f);
    switch (app::Random::Rand(5)) {
    case 0:
        offset.y += radius * obj().param().aquarock().mShakeRate;
        break;
    case 1:
        offset.x += radius * obj().param().aquarock().mShakeRate;
        break;
    case 2:
        offset.y -= radius * obj().param().aquarock().mShakeRate;
        break;
    case 3:
        offset.x -= radius * obj().param().aquarock().mShakeRate;
        break;
    }
    obj().model().setViewOffset(offset);
}

void StateMove::mfSetModelVisible() {
    if (_c) {
        if (obj().model().isVisible()) {
            obj().model().setVisibility(false);
            obj().effect().state().releaseAndVanish();
        }
    } else {
        if (!obj().model().isVisible()) {
            obj().model().setVisibility(true);
        }
    }
}

f32 StateMove::mfCheckRotate(f32 rot) {
    if (rot >= 180.0f) {
        rot -= 360.0f;
    } else if (rot < -180.0f) {
        rot += 360.0f;
    }
    return rot;
}

f32 StateMove::mfCheckRotate360(f32 rot) {
    if (rot >= 360.0f) {
        rot -= 360.0f;
    } else if (rot < 0.0f) {
        rot += 360.0f;
    }
    return rot;
}

f32 StateMove::mfGetRotByDirType(map::BinEnemyDirType dirType) {
    f32 rot = 0.0f;
    switch (dirType) {
    case 4:
        rot = 0.0f;
        break;
    case 7:
        rot = 45.0f;
        break;
    case 3:
        rot = 90.0f;
        break;
    case 9:
        rot = 135.0f;
        break;
    case 5:
        rot = -180.0f;
        break;
    case 8:
        rot = -135.0f;
        break;
    case 2:
        rot = -90.0f;
        break;
    case 6:
        rot = -45.0f;
        break;
    }
    return rot;
}

map::BinEnemyDirType StateMove::mfNormalToDirType(hel::math::Vector2 normal) {
    f32 rot = mfCheckRotate360(5.0f + hel::math::Math::Atan2DegF(-normal.x, normal.y));
    return static_cast<map::BinEnemyDirType>(dirTypeMapTbl[static_cast<u32>(rot / 10.0f)]);
}

map::BinEnemyDirType StateMove::mfNormalToDirTypeNururi(hel::math::Vector2 normal) {
    f32 rot = mfCheckRotate360(22.5f + hel::math::Math::Atan2DegF(-normal.x, normal.y));
    return static_cast<map::BinEnemyDirType>(dirTypeNururiTbl[static_cast<u32>(rot / 45.0f)]);
}

map::BinEnemyDirType StateMove::mfNewDirType(map::BinEnemyDirType from, map::BinEnemyDirType to) {
    map::BinEnemyDirType result = static_cast<map::BinEnemyDirType>(0);
    if (2 <= from && from <= 9 && 2 <= to && to <= 9) {
        result = static_cast<map::BinEnemyDirType>(newDirTbl[from - 2][to - 2].mDirType);
    }
    return result;
}

f32 StateMove::mfNewRotDir(map::BinEnemyDirType from, map::BinEnemyDirType to) {
    f32 result = 0.0f;
    if (2 <= from && from <= 9 && 2 <= to && to <= 9) {
        result = newDirTbl[from - 2][to - 2].mRot;
    }
    return result;
}

StateMove::RayCheckData StateMove::mfGetRayCheckData(f32 angle, hel::math::Vector2 pos, f32 length) {
    RayCheckData data;
    f32 rot = mfGetRotByDirType(mDirType);
    hel::math::Vector2 dir(length * hel::math::Math::SinDegF(rot + angle), length * hel::math::Math::CosDegF(rot + angle));
    hel::math::Vector2 back(length * hel::math::Math::SinDegF(180.0f + rot), length * hel::math::Math::CosDegF(180.0f + rot));
    data._0 = pos + back;
    data._8 = dir - back;
    return data;
}

StateMove::RayCheckData StateMove::mfGetRayCheckData2(f32 angle, f32 angle2, hel::math::Vector2 pos, f32 length) {
    RayCheckData data;
    f32 rot = mfGetRotByDirType(mDirType);
    hel::math::Vector2 dir(length * hel::math::Math::SinDegF(rot + angle), length * hel::math::Math::CosDegF(rot + angle));
    hel::math::Vector2 back(length * hel::math::Math::SinDegF(rot + angle2), length * hel::math::Math::CosDegF(rot + angle2));
    data._0 = pos + back;
    data._8 = dir - back;
    return data;
}

StateMove::MapHitResult StateMove::mfMapCheckPoint(hel::math::Vector2 pos, hel::math::Vector2 dir) {
    MapHitResult result;
    result.mIsHit = false;
    result._4 = hel::math::Vector2(0.0f, 0.0f);
    mcoll::detail::DetectArg arg;
    arg.setVelocity(dir);
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
        mcoll::detail::CollidedInfo info = detect.collidedLog(0).info();
        result.mIsHit = true;
        _44 = info.intersectPos();
        hel::geo2d::Edge edge = info.collideTarget().edge();
        result._4 = edge._10;
        result._4.normalize();
    }
    return result;
}

StateMove::MapHitResult StateMove::mfNururiHitCheck() {
    MapHitResult result;
    result.mIsHit = false;
    result._4 = hel::math::Vector2(0.0f, 0.0f);
    return result;
}

void StateMove::mfMapCheck() {
    f32 radius = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).getRadius();
    hel::math::Vector2 pos = obj().model().model().nodes().at(2).worldMtx().getT().getXY();
    RayCheckData data;
    MapHitResult result;
    hel::math::Vector2 normal(0.0f, 0.0f);
    bool isHit = false;
    data = mfGetRayCheckData(0.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData(45.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData(-45.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData(90.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData(-90.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData2(0.0f, 45.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    data = mfGetRayCheckData2(0.0f, -45.0f, pos, radius);
    result = mfMapCheckPoint(data._0, data._8);
    if (result.mIsHit) {
        isHit = true;
        normal += result._4;
    }
    if (isHit) {
        if (normal.isZeroLoose(0.00001f)) {
            normal = hel::math::Vector2(0.0f, 0.0f);
            isHit = false;
        } else {
            normal.normalize();
        }
    }
    result = mfNururiHitCheck();
    if (result.mIsHit) {
        normal += result._4;
        if (normal.isZeroLoose(0.00001f)) {
            normal = hel::math::Vector2(0.0f, 0.0f);
            isHit = false;
            result.mIsHit = false;
        } else {
            normal.normalize();
        }
    }
    map::BinEnemyDirType dirType = mDirType;
    if (isHit) {
        dirType = mfNormalToDirType(normal);
    } else if (result.mIsHit) {
        isHit = true;
        dirType = mfNormalToDirTypeNururi(normal);
    }
    if (isHit) {
        mIsShake = true;
        if (!_c) {
            obj().effect().normal().requestP(static_cast<effect::Kind>(0), _44.toVector3());
            obj().soundSE().start(0x558);
        }
        f32 rotDir = mfNewRotDir(mDirType, dirType);
        if (rotDir != 0.0f) {
            mRotSpeed = rotDir * hel::math::Math::Abs(mRotSpeed);
        }
        mDirType = mfNewDirType(mDirType, dirType);
    }
}

}
}
}
}
