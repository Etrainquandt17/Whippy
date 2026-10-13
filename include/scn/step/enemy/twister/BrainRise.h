#ifndef SCN_STEP_ENEMY_TWISTER_BRAINRISE_H
#define SCN_STEP_ENEMY_TWISTER_BRAINRISE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

class BrainRise : public BrainBase {
public:
    BrainRise(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::twister

#endif
