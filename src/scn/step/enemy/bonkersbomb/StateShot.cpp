#include "scn/step/enemy/bonkersbomb/StateShot.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
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
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/bonkersbomb/ParamData.h"
#include "scn/step/enemy/bonkersbomb/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    const ParamData& param = obj().param().bonkersbomb();
    mRot = obj().model().rotCtrl().getRotV();
    obj().footState().setAir();
    obj().model().reqScript(0);
    if (obj().size() == 0) {
        obj().soundSE().start(0x559);
    } else {
        obj().soundSE().start(0x5a4);
    }
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData::Shot& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mShot : obj().param().bonkersbomb().mShotBig;
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, obj().target().isRightDir(), param.mRotSpeed);
    obj().model().rotCtrl().initRotV(mRot);
}

void StateShot::procMove() {
    const ParamData::Shot& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mShot : obj().param().bonkersbomb().mShotBig;
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), param.mFall);
}

void StateShot::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}
}
}
}
