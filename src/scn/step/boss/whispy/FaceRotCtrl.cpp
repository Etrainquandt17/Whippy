#include "scn/step/boss/whispy/FaceRotCtrl.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

const u32 T_TARGET_NODE[] = { 9, 10, 11 };

}

FaceRotCtrl::FaceRotCtrl(Boss& boss) : mBoss(boss) {}

void FaceRotCtrl::setRotate(f32 rot) {
    while (rot >= 360.0f) {
        rot -= 360.0f;
    }
    while (rot < 0.0f) {
        rot += 360.0f;
    }
    Matrix34 mtx = Matrix34::CreateRotXYZDeg(Vector3(0.0f, rot, 0.0f));
    for (u32 i = 0; i < 3; i++) {
        mBoss.model().model().nodes().at(T_TARGET_NODE[i]).localMtx().setRTMtx(mtx);
    }
}

void FaceRotCtrl::reset() {
    for (u32 i = 0; i < 3; i++) {
        mBoss.model().model().nodes().at(T_TARGET_NODE[i]).localMtx().reset();
    }
}

}}}}  // namespace scn::step::boss::whispy
