#include "scn/step/enemy/sodory/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Model.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sodory/ParamData.h"
#include "scn/step/hero/Manager.h"
#include "snd/SERequestor.h"

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

void Custom::setEyeMtx(hel::math::Matrix34 mtx) {
    obj().model().model().nodes().at(4).localMtx().setRTMtx(mtx);
}

void Custom::setEyeDirection() {
    hel::math::Vector3 diff = getPlayerDiff();
    hel::math::Vector3 rot(0.0f, 0.0f, hel::math::Math::Atan2DegF(diff.y * obj().target().getSign(), -diff.x));
    setEyeMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
}

// TODO: the link dropped this one; the body is a guess with the map's size (0x9c bytes).
void Custom::setEyeDirectionOffs(f32 offs) {
    hel::math::Vector3 diff = getPlayerDiff();
    hel::math::Vector3 rot(0.0f, 0.0f, offs + hel::math::Math::Atan2DegF(diff.y * obj().target().getSign(), -diff.x));
    setEyeMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
}

hel::math::Vector3 Custom::getPlayerDiff() {
    hel::math::Vector3 nodePos = obj().model().model().nodes().at(4).worldMtx().getT();
    hel::math::Vector3 playerPos = obj().comp().heroManager().getNearestPlayerPos(nodePos);
    playerPos.y += 0.5f;
    return nodePos - playerPos;
}

void Custom::addOffsY() {
    if (0.0f != mOffsY) {
        hel::math::Vector3 pos = obj().location().pos();
        pos.y += mOffsY;
        mOffsY = 0.0f;
        obj().location().setPos(pos);
    }
}

void Custom::setPosYR(f32 rot) {
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, -obj().param().sodory().mBodyOffsY, 0.0f));
    hel::math::Matrix34 rotMtx = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, -1.0f), rot);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx * rotMtx);
    mtx = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, obj().param().sodory().mHeadOffsY, 0.0f));
    obj().model().model().nodes().at(2).localMtx().setRTMtx(mtx);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::sodory
