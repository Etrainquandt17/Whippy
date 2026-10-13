#ifndef SCN_STEP_ENEMY_PLUID_BRAINRANDOMSTAY_H
#define SCN_STEP_ENEMY_PLUID_BRAINRANDOMSTAY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

class BrainRandomStay : public BrainBase {
public:
    BrainRandomStay(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::pluid

#endif
