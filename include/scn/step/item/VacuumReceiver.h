#ifndef SCN_STEP_ITEM_VACUUMRECEIVER_H
#define SCN_STEP_ITEM_VACUUMRECEIVER_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace item {

// TODO: members and the other functions.
class VacuumReceiver {
public:
    void setIsValid(bool isValid);
    hel::math::Vector2 getAttackerPos() const;
    void setEndVacuumed();
};

}}}  // namespace scn::step::item

#endif
