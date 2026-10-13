#ifndef SCN_STEP_ENEMY_BRONTOBURT_BRAINWHISPY_H
#define SCN_STEP_ENEMY_BRONTOBURT_BRAINWHISPY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

class BrainWhispy : public BrainBase {
public:
    BrainWhispy(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::brontoburt

#endif
