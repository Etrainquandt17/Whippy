#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATESHOT3D_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATESHOT3D_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

// TODO: stub
class StateShot3D : public StateBase {
public:
    StateShot3D(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
