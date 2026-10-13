#ifndef SCN_STEP_ENEMY_BARRACU_BRAINPURSUIT_H
#define SCN_STEP_ENEMY_BARRACU_BRAINPURSUIT_H

#include "scn/step/enemy/BrainBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

class BrainPursuit : public BrainBase {
public:
    BrainPursuit(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::barracu

#endif
