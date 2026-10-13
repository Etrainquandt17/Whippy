#ifndef SCN_STEP_ENEMY_GORDO_BRAINWHISPY_H
#define SCN_STEP_ENEMY_GORDO_BRAINWHISPY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

class BrainWhispy : public BrainBase {
public:
    BrainWhispy(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::gordo

#endif
