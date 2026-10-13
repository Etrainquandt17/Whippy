#ifndef SCN_STEP_ENEMY_GORDO_BRAINMOVE_H
#define SCN_STEP_ENEMY_GORDO_BRAINMOVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

class BrainMove : public BrainBase {
public:
    BrainMove(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::gordo

#endif
