#ifndef SCN_STEP_ENEMY_PARASOL_BRAINRISE_H
#define SCN_STEP_ENEMY_PARASOL_BRAINRISE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

class BrainRise : public BrainBase {
public:
    BrainRise(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::parasol

#endif
