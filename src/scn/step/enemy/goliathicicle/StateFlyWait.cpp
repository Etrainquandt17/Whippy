#include "scn/step/enemy/goliathicicle/StateFlyWait.h"

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
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/goliathicicle/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

StateFlyWait::StateFlyWait(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    obj().footState().setAir();
    obj().nururi().setCanNururi(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(0);
    mRot = app::Random::RandF(0.0f, 360.0f);
    {
        g3d::NodeAccessor node = obj().model().model().nodes().at(0);
        hel::math::Vector3 rot(0.0f, mRot, 0.0f);
        node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
    }
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
}

StateFlyWait::~StateFlyWait() {
    obj().mapColl().setValid(true);
}

void StateFlyWait::procAnim() {
    if (obj().signal().isValid()) {
        u32 signal = obj().signal().get();
        obj().signal().clear();
        switch (signal) {
        case 2: {
            hel::math::Vector3 pos = obj().location().pos();
            pos.y -= 0.6f;
            obj().location().setPos(pos);
            obj().model().shake().request(static_cast<chara::ShakeKind>(3));
            break;
        }
        case 3:
            obj().stateChanger().setNextState<StateFall, Enemy*, f32>(objPtr(), mRot);
            break;
        }
    }
}

void StateFlyWait::procMove() {}

void StateFlyWait::procFixPos() {}

}
}
}
}
