#ifndef SCN_STEP_ENEMY_BLIPPER_BRAINFATTYBUFFER_H
#define SCN_STEP_ENEMY_BLIPPER_BRAINFATTYBUFFER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

class BrainFattyBuffer : public BrainBase {
public:
    BrainFattyBuffer(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::blipper

#endif
