#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINVERTICALSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINVERTICALSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainVerticalShot : public BrainBase {
public:
    BrainVerticalShot(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
