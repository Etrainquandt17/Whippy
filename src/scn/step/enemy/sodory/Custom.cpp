#include "scn/step/enemy/sodory/Custom.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sodory/ParamData.h"
#include "scn/step/hero/Manager.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mSpeed(0.0f), mAnimRate(0.0f), mBasePosX(0.0f), mOffsY(0.0f), mFrame(obj().param().sodory().mMoveFrame / 2) {
    const ParamData& param = obj().param().sodory();
    switch (obj().level()) {
    case 0:
        mSpeed = param.mSpeed[0];
        break;
    case 1:
        mSpeed = param.mSpeed[1];
        break;
    default:
        mSpeed = param.mSpeed[2];
        break;
    }
    mAnimRate = mSpeed / 0.02f;
    mBasePosX = obj().location().pos().x;
    mOffsY = param.mFlyOffsY;
}

bool Custom::onInit() {
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(8, Utility::GetModelScaleBySizeType(obj()) * 0.5f);
    return false;
}

bool Custom::onDamaged() {
    onInit();
    return false;
}

f32 Custom::getSpeed() const {
    return mSpeed;
}

f32 Custom::getAnimRate() const {
    return mAnimRate;
}

void Custom::resetBasePosX() {
    mBasePosX = 0.0f;
}

void Custom::setBasePosX() {
    if (0.0f == mBasePosX) {
        mBasePosX = obj().location().pos().x;
    }
}

void Custom::setBasePosX(f32 x) {
    mBasePosX = x;
}

f32 Custom::getBasePosX() {
    return mBasePosX;
}

void Custom::setFrame() {
    mFrame = obj().param().sodory().mMoveFrame;
}

u32 Custom::getFrame() const {
    return mFrame;
}

void Custom::setDirectionAll() {
    setDirection();
    setEyeDirection();
}

void Custom::setDirection() {
    obj().model().rotCtrl().setRotHTarget(obj().target().isRightDir() ? 180.0f : 0.0f);
    obj().model().rotCtrl().setRotHIntpRate(1.0f);
}

void Custom::setEyeMtx(Matrix34 mtx) {
    obj().model().model().nodes().at(4).localMtx().setRTMtx(mtx);
}

void Custom::setEyeDirection() {
    Vector3 diff = getPlayerDiff();
    Vector3 rot(0.0f, 0.0f, Math::Atan2DegF(diff.y * obj().target().getSign(), -diff.x));
    setEyeMtx(Matrix34::CreateRotXYZDeg(rot));
}

// TODO: the link dropped this one; the body is a guess with the map's size (0x9c bytes).
void Custom::setEyeDirectionOffs(f32 offs) {
    Vector3 diff = getPlayerDiff();
    Vector3 rot(0.0f, 0.0f, offs + Math::Atan2DegF(diff.y * obj().target().getSign(), -diff.x));
    setEyeMtx(Matrix34::CreateRotXYZDeg(rot));
}

Vector3 Custom::getPlayerDiff() {
    Vector3 nodePos = obj().model().model().nodes().at(4).worldMtx().getT();
    Vector3 playerPos = obj().comp().heroManager().getNearestPlayerPos(nodePos);
    playerPos.y += 0.5f;
    return nodePos - playerPos;
}

void Custom::addOffsY() {
    if (0.0f != mOffsY) {
        Vector3 pos = obj().location().pos();
        pos.y += mOffsY;
        mOffsY = 0.0f;
        obj().location().setPos(pos);
    }
}

void Custom::setPosYR(f32 rot) {
    Matrix34 mtx = Matrix34::CreateTrans(Vector3(0.0f, -obj().param().sodory().mBodyOffsY, 0.0f));
    Matrix34 rotMtx = Matrix34::CreateRotAxisDeg(Vector3(0.0f, 0.0f, -1.0f), rot);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx * rotMtx);
    mtx = Matrix34::CreateTrans(Vector3(0.0f, obj().param().sodory().mHeadOffsY, 0.0f));
    obj().model().model().nodes().at(2).localMtx().setRTMtx(mtx);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::sodory
