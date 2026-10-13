#include "scn/step/enemy/waddledoo/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/waddledoo/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(9);
}

void StateJump::procAnim() {
    if (obj().model().isAllEnd()) {
        if (static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) == 9) {
            obj().model().reqScript(8);
            obj().footState().setAir();
            obj().move().setSpeedV(obj().param().waddledoo().mJumpSpeed);
        } else {
            obj().model().reqScript(1);
        }
    }
}

void StateJump::procMove() {
    if (static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) != 9) {
        obj().move().airAccelFall(obj().target().isRightDir(), obj().param().waddledoo().mJumpAccel,
                                  obj().param().waddledoo().mJumpFall);
    }
}

void StateJump::procFixPos() {
    if (static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) == 1) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
        }
    }
    if (obj().mapColl().result().isHitWall()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}}}}  // namespace scn::step::enemy::waddledoo
