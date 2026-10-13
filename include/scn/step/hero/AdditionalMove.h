#ifndef SCN_STEP_HERO_ADDITIONALMOVE_H
#define SCN_STEP_HERO_ADDITIONALMOVE_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class AdditionalMove {
public:
    void setForbidChangeState(bool isForbid);
    void setValid(bool isValid);
    void setEnableAirFlowOffset(bool isEnable);
    const hel::math::Vector2& airFlowVector() const;
};

}}}  // namespace scn::step::hero

#endif
