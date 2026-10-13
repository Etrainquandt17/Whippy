#include "scn/step/enemy/metalgeneralbomb/StateShot.h"

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
#include "scn/step/enemy/metalgeneralbomb/ParamData.h"
#include "scn/step/enemy/metalgeneralbomb/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    mRot = obj().model().rotCtrl().getRotV();
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData& param = obj().param().metalgeneralbomb();
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, obj().target().isRightDir(), param.mRotSpeed);
    obj().model().rotCtrl().initRotV(mRot);
}

void StateShot::procMove() {
    const ParamData& param = obj().param().metalgeneralbomb();
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateShot::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (obj().mapColl().isHitAll()) {
        obj().soundSE().start(0x3f0);
        if (result.mIsHitFloor) {
            obj().stateChanger().setNextState<StateLanding, Enemy*, bool>(objPtr(), true);
        } else {
            obj().stateChanger().setNextState<StateLanding, Enemy*, bool>(objPtr(), false);
        }
    }
}

}}}}  // namespace scn::step::enemy::metalgeneralbomb
