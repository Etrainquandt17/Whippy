#ifndef SCN_STEP_ENEMY_DEGOUT_BRAINWAITANDCHASE_H
#define SCN_STEP_ENEMY_DEGOUT_BRAINWAITANDCHASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

class BrainWaitAndChase : public BrainBase {
public:
    BrainWaitAndChase(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::degout

#endif
