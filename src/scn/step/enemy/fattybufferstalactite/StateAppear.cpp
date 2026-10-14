#include "scn/step/enemy/fattybufferstalactite/StateAppear.h"

#include "app/Random.h"
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
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/fattybufferstalactite/ParamData.h"
#include "scn/step/enemy/fattybufferstalactite/StateFall.h"
#include "snd/SERequestor.h"

using app::Random;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    const ParamData& param = obj().param().fattybufferstalactite();
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().mapColl().setValid(false);
    obj().model().rotCtrl().setValid(false);
    mRot = Random::RandF(0.0f, 360.0f);
    obj().model().model().nodes().at(0).localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot, 0.0f)));
    Vector3 pos = obj().location().pos();
    pos.y += param.mEffectOffsetY;
    obj().effect().state().requestP(static_cast<effect::Kind>(0x13e), pos);
    obj().soundSE().start(0x35d);
}

void StateAppear::procAnim() {
    const ParamData& param = obj().param().fattybufferstalactite();
    Vector3 pos = obj().location().pos();
    if (obj().signal().isValid()) {
        switch (obj().signal().get()) {
        case 1:
            obj().signal().clear();
            pos.y -= param.mAppearStep;
            obj().location().setPos(pos);
            break;
        case 2:
            obj().signal().clear();
            obj().mapColl().setValid(true);
            obj().stateChanger().setNextState<StateFall, Enemy*, f32>(objPtr(), mRot);
            break;
        }
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::fattybufferstalactite
