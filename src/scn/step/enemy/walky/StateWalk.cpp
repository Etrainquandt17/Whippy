#include "scn/step/enemy/walky/StateWalk.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/walky/Custom.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace walky {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    if (obj().model().anim().currentG3DAnimIndex() != 3) {
        obj().model().reqScript(3);
    }
    obj().model().setFrameRate(DynamicCastToRef<Custom, ICustom>(obj().custom()).getAnimRate());
    obj().brainCtrl().toValid();
}

StateWalk::~StateWalk() {
    obj().model().setFrameRate(1.0f);
}

void StateWalk::procAnim() {}

void StateWalk::procMove() {
    gobj::MoveParamAccel accel = gobj::MoveParamAccel::Create(DynamicCastToRef<Custom, ICustom>(obj().custom()).getSpeed(), 0.003f, 0.001f);
    obj().move().groundAccel(obj().target().isRightDir(), accel);
}

void StateWalk::procFixPos() {
    if (obj().mapColl().result()._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walky
