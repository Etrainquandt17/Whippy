#include "scn/step/enemy/sheld/StateEscape.h"

#include "g3d/NodeAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateEscape::StateEscape(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(13);
    obj().model().model().nodes().at(2).setVisibility(false);
    obj().objColl().bodyColl().unsetAttackTypeOver();
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).initEscape();
    obj().brainCtrl().toValid();
}

StateEscape::~StateEscape() {}

void StateEscape::procAnim() {}

void StateEscape::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(0.05f, 0.001f, 0.001f));
}

void StateEscape::procFixPos() {
    if (obj().mapColl().result()._2 || Utility::ChkNururiByDir(obj(), 0.1f)) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
