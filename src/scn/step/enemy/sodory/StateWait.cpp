#include "scn/step/enemy/sodory/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sodory/Custom.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame < custom.getFrame()) {
        mFrame++;
        if (mFrame >= custom.getFrame()) {
            obj().brainCtrl().toValid();
        }
    }
}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setDirectionAll();
}

}}}}  // namespace scn::step::enemy::sodory
