#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINSHARPSHOOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINSHARPSHOOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainSharpshoot : public BrainBase {
public:
    BrainSharpshoot(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
