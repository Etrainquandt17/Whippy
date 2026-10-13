#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINSATELLITE_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINSATELLITE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainSatellite : public BrainBase {
public:
    BrainSatellite(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
