#ifndef SCN_STEP_ENEMY_JUCKLE_BRAINFOLLOW_H
#define SCN_STEP_ENEMY_JUCKLE_BRAINFOLLOW_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

class BrainFollow : public BrainBase {
public:
    BrainFollow(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::juckle

#endif
