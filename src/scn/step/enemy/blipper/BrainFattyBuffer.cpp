#include "scn/step/enemy/blipper/BrainFattyBuffer.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/blipper/StateFattyBufferAppearFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

BrainFattyBuffer::BrainFattyBuffer(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFattyBuffer::onStart() {
    obj().stateChanger().setNextState<StateFattyBufferAppearFall, Enemy*>(&obj());
    return true;
}

bool BrainFattyBuffer::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::blipper
