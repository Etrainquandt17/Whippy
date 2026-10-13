#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINDIVIDEBOMB_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINDIVIDEBOMB_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

class BrainDivideBomb : public BrainBase {
public:
    BrainDivideBomb(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
