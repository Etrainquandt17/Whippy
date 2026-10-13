#ifndef SCN_STEP_CORE_MOVELIMIT_H
#define SCN_STEP_CORE_MOVELIMIT_H

#include "hel/geo/Rect.h"

namespace scn {
namespace step {
namespace core {

// TODO: members and the other functions.
class MoveLimit {
public:
    void reset();
    void setLimitRect(const hel::geo::Rect& rect);
    hel::geo::Rect getLimitRect() const;
};

}}}  // namespace scn::step::core

#endif
