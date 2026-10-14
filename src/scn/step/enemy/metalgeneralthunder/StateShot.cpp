#include "scn/step/enemy/metalgeneralthunder/StateShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/metalgeneralthunder/ParamData.h"
#include "scn/step/enemy/metalgeneralthunder/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    mRot = obj().model().rotCtrl().getRotV();
    obj().footState().setAir();
    obj().model().reqScript(0);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData& param = obj().param().metalgeneralthunder();
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, obj().target().isRightDir(), param.mRotSpeed);
    obj().model().rotCtrl().initRotV(mRot);
}

void StateShot::procMove() {
    const ParamData& param = obj().param().metalgeneralthunder();
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateShot::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (obj().mapColl().isHitAll()) {
        if (result.mIsHitFloor) {
            obj().soundSE().start(0x3f0);
            obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        } else {
            obj().move().setSpeedH(-obj().move().velocity().x);
        }
    }
}

}}}}  // namespace scn::step::enemy::metalgeneralthunder
