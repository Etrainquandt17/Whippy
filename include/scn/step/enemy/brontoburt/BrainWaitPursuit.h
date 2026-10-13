#ifndef SCN_STEP_ENEMY_BRONTOBURT_BRAINWAITPURSUIT_H
#define SCN_STEP_ENEMY_BRONTOBURT_BRAINWAITPURSUIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

class BrainWaitPursuit : public BrainBase {
public:
    BrainWaitPursuit(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::brontoburt

#endif
