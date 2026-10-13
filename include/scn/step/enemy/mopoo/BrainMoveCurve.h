#ifndef SCN_STEP_ENEMY_MOPOO_BRAINMOVECURVE_H
#define SCN_STEP_ENEMY_MOPOO_BRAINMOVECURVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

class BrainMoveCurve : public BrainBase {
public:
    BrainMoveCurve(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
