#include "scn/step/enemy/babut/StateHang.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateHang::StateHang(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().brainCtrl().toValid();
}

void StateHang::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

}}}}  // namespace scn::step::enemy::babut
