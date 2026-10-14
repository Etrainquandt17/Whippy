#include "scn/step/boss/whispy/TSCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Matrix34.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

const u32 T_TRUNKNODE_TABLE[] = { 4, 5, 6, 7, 8 };

}

TSCtrl::TSCtrl(Boss& boss) : mBoss(boss) {}

void TSCtrl::setTrunkScale(f32 scale) {
    Vector3 nodeScale(scale, 1.0f, scale);
    for (u32 i = 0; i < 5; i++) {
        mBoss.model().model().nodes().at(T_TRUNKNODE_TABLE[i]).localMtx().setScale(nodeScale);
    }
}

void TSCtrl::setBaseTrans(const Vector3& trans) {
    mBoss.model().model().nodes().at(3).localMtx().setRTMtx(Matrix34::CreateTrans(trans));
}

void TSCtrl::setBaseScale(const Vector3& scale) {
    mBoss.model().model().nodes().at(3).localMtx().setScale(scale);
}

}}}}  // namespace scn::step::boss::whispy
