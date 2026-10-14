#include "scn/step/boss/lowper/StateHide.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateHide::StateHide(Boss* boss) : StateBase(boss) {
    boss->model().setVisibility(false);
}

StateHide::~StateHide() {
    obj().model().setVisibility(true);
}

void StateHide::procAnim() {}

void StateHide::procMove() {}

void StateHide::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
