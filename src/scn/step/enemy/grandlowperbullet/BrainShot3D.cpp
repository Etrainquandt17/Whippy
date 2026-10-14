#include "scn/step/enemy/grandlowperbullet/BrainShot3D.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/grandlowperbullet/StateShot3D.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

BrainShot3D::BrainShot3D(Enemy& enemy) : BrainBase(enemy) {}

bool BrainShot3D::onStart() {
    obj().stateChanger().setNextState<StateShot3D, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
