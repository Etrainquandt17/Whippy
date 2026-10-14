#include "scn/step/boss/mahoroaroah/StateWarp.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

StateWarp::StateWarp(Boss* boss, WarpKind kind) : StateBase(boss), mKind(kind) {
    obj().model().setVisibility(true);
}

StateWarp::~StateWarp() {
    obj().model().setVisibility(true);
}

void StateWarp::procAnim() {
    if (mKind == WARP_KIND_0 && obj().model().isAllEnd()) {
        obj().model().setVisibility(false);
    }
}

void StateWarp::procMove() {}

void StateWarp::procFixPos() {}

}}}}  // namespace scn::step::boss::mahoroaroah
