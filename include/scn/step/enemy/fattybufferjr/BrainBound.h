#ifndef SCN_STEP_ENEMY_FATTYBUFFERJR_BRAINBOUND_H
#define SCN_STEP_ENEMY_FATTYBUFFERJR_BRAINBOUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

class BrainBound : public BrainBase {
public:
    BrainBound(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::fattybufferjr

#endif
