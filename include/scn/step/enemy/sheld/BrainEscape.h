#ifndef SCN_STEP_ENEMY_SHELD_BRAINESCAPE_H
#define SCN_STEP_ENEMY_SHELD_BRAINESCAPE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

class BrainEscape : public BrainBase {
public:
    BrainEscape(Enemy& enemy);
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::sheld

#endif
