#ifndef SCN_STEP_ENEMY_NRUFF_BRAINRUN_H
#define SCN_STEP_ENEMY_NRUFF_BRAINRUN_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

class BrainRun : public BrainBase {
public:
    BrainRun(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::nruff

#endif
