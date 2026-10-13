#ifndef SCN_STEP_ENEMY_COMMON_BRAINMAHOROA1_H
#define SCN_STEP_ENEMY_COMMON_BRAINMAHOROA1_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainMahoroa1 : public BrainBase {
public:
    BrainMahoroa1(Enemy& enemy, bool _8);
    virtual bool onStart();
    virtual bool onRecover();

private:
    bool _8;
};

}}}}  // namespace scn::step::enemy::common

#endif
