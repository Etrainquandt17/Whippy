#include "scn/step/enemy/twister/StateFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/twister/Custom.h"
#include "scn/step/enemy/twister/ParamData.h"
#include "scn/step/enemy/twister/StateWait.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace twister {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().model().anim().setFrameRate(1.0f);
    custom.setThetaY(0.0f);
    custom.setThetaX(0.0f);
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(custom.getThetaX(), custom.getThetaY(), 0.0f)));
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    const ParamData& param = obj().param().twister();
    obj().move().airDecelFall(param.mFallDecel, param.mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && obj().footState().isAir()) {
        obj().model().reqScript(8);
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::enemy::twister
