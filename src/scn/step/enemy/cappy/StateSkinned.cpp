#include "scn/step/enemy/cappy/StateSkinned.h"

#include "g3d/NodeAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "scn/step/enemy/cappy/ParamData.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/common/StateWalkAround.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

StateSkinned::StateSkinned(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().cappy();
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().model().model().nodes().at(2).setVisibility(false);
    obj().model().model().nodes().at(3).setVisibility(true);
    obj().objColl().setBodyCollStateXlu();
    f32 speed = param.mSkinnedSpeedH * -obj().target().getSign();
    obj().move().setSpeedH(speed);
    obj().move().setSpeedV(param.mSkinnedSpeedV);
    u32 level = obj().vacuumReceiver().getResistLevelTotal();
    obj().vacuumReceiver().setResistLevelInterim(level + 1, 32);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setCap(false);
}

StateSkinned::~StateSkinned() {
    obj().objColl().setBodyCollStateNormal();
}

void StateSkinned::procMove() {
    const ParamData& param = obj().param().cappy();
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateSkinned::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
    mFrame++;
    if (mFrame == 30) {
        obj().objColl().setBodyCollStateNormal();
    }
    if (mFrame == 45) {
        if (obj().variation() == 9) {
            obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
        } else if (obj().variation() == 1) {
            obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateWalkAround, Enemy*>(objPtr());
        }
    }
}

}
}
}
}
