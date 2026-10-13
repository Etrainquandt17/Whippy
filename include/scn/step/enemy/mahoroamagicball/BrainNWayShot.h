#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINNWAYSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINNWAYSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainNWayShot : public BrainBase {
public:
    BrainNWayShot(Enemy& enemy, bool _1);
    virtual bool onStart();

private:
    bool _8;
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
