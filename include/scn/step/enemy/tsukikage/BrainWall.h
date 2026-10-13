#ifndef SCN_STEP_ENEMY_TSUKIKAGE_BRAINWALL_H
#define SCN_STEP_ENEMY_TSUKIKAGE_BRAINWALL_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

class BrainWall : public BrainBase {
public:
    BrainWall(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::tsukikage

#endif
