#ifndef SCN_STEP_HERO_MOVELIMITRESPONSECTRL_H
#define SCN_STEP_HERO_MOVELIMITRESPONSECTRL_H

#include "hel/math/Vector3.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class MoveLimitResponseCtrl {
public:
    MoveLimitResponseCtrl();

    void setResponseDead();
    void setResponseSpaceJumpToMainPlayer();
    void setResponseSpaceJumpToPos(const hel::math::Vector3& pos);
    void resetResponse();
};

}}}  // namespace scn::step::hero

#endif
