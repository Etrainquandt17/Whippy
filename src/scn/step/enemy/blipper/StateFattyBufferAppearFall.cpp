#include "scn/step/enemy/blipper/StateFattyBufferAppearFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/blipper/ParamData.h"
#include "scn/step/enemy/common/StateLanding.h"

using g3d::NodeAccessor;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateFattyBufferAppearFall::StateFattyBufferAppearFall(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    obj().footState().setAir();
    obj().model().reqScript(11);
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().worldCage().setIsValid(true);
}

StateFattyBufferAppearFall::~StateFattyBufferAppearFall() {
    obj().nururi().setValid(true);
    obj().nururi().setCanNururi(true);
    obj().model().model().nodes().at(1).localMtx().reset();
}

void StateFattyBufferAppearFall::procAnim() {
    const ParamData& param = obj().param().blipper();
    mRot += param.mFattyBufferAppearRotSpeed;
    NodeAccessor node = obj().model().model().nodes().at(1);
    Vector3 rot(0.0f, 0.0f, mRot * -obj().target().getSign());
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(rot));
}

void StateFattyBufferAppearFall::procMove() {
    const ParamData& param = obj().param().blipper();
    obj().move().airDecelFall(param.mFattyBufferDecel, param.mFattyBufferFall);
}

void StateFattyBufferAppearFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::blipper
