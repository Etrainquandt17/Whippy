#include "scn/step/enemy/poppybrojrbomb/StateWait.h"

#include "gobj/FootState.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojrbomb {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
}

StateWait::~StateWait() {}

}}}}  // namespace scn::step::enemy::poppybrojrbomb
