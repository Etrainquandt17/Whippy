#ifndef SCN_STEP_ENEMY_OWGULF_BRAINFLYSTRAIGHT_H
#define SCN_STEP_ENEMY_OWGULF_BRAINFLYSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

class BrainFlyStraight : public BrainBase {
public:
    BrainFlyStraight(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::owgulf

#endif
