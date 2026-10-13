#ifndef SCN_STEP_CARRYITEM_VACUUMRECEIVER_H
#define SCN_STEP_CARRYITEM_VACUUMRECEIVER_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace carryitem {

class VacuumReceiver {
public:
    void setIsValid(bool isValid);
    void clearIgnoreAttacker();
    hel::math::Vector2 getAttackerPos() const;
    void setEndVacuumed();
};

}}}  // namespace scn::step::carryitem

#endif
