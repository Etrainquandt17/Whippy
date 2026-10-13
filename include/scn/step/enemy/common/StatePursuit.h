#ifndef SCN_STEP_ENEMY_COMMON_STATEPURSUIT_H
#define SCN_STEP_ENEMY_COMMON_STATEPURSUIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StatePursuit : public StateBase {
public:
    StatePursuit(Enemy* enemy);
    virtual ~StatePursuit();
};

}}}}  // namespace scn::step::enemy::common

#endif
