#ifndef SCN_STEP_ENEMY_PARASOLDEE_BRAINRELEASE_H
#define SCN_STEP_ENEMY_PARASOLDEE_BRAINRELEASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldee {

class BrainRelease : public BrainBase {
public:
    BrainRelease(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual void update();
};

}}}}  // namespace scn::step::enemy::parasoldee

#endif
