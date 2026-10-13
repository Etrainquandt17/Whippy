#ifndef SCN_STEP_ENEMY_STARMAN_BRAINJUMP_H
#define SCN_STEP_ENEMY_STARMAN_BRAINJUMP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

class BrainJump : public BrainBase {
public:
    BrainJump(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
    virtual void update();
};

}}}}  // namespace scn::step::enemy::starman

#endif
