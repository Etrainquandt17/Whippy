#include "scn/step/enemy/fattybufferstalactite/StateFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/fattybufferstalactite/ParamData.h"
#include "scn/step/enemy/fattybufferstalactite/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {

StateFall::StateFall(Enemy* enemy, f32 rot) : StateBase(enemy), mRot(rot) {
    obj().footState().setAir();
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(0.5f, 0.5f, 0.5f));
    obj().soundSE().start(0x35e);
}

void StateFall::procAnim() {
    const ParamData& param = obj().param().fattybufferstalactite();
    mRot += param.mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    obj().model().model().nodes().at(0).localMtx().setRTMtx(
        hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, mRot, 0.0f)));
}

void StateFall::procMove() {
    const ParamData& param = obj().param().fattybufferstalactite();
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateFall::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::fattybufferstalactite
