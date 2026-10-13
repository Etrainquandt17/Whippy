#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINWARPHOLEPOPUP_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINWARPHOLEPOPUP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainWarpHolePopup : public BrainBase {
public:
    BrainWarpHolePopup(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
