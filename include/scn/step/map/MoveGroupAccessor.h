#ifndef SCN_STEP_MAP_MOVEGROUPACCESSOR_H
#define SCN_STEP_MAP_MOVEGROUPACCESSOR_H

#include "hel/math/Vector2.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "types.h"

namespace scn {
namespace step {
namespace map {

// TODO: members.
class MoveGroupAccessor {
public:
    hel::math::Vector2 deltaSafe(const mcoll::detail::MoveGridGroupId& id) const;
    hel::math::Vector2 deltaSafe(u32 no) const;
    hel::math::Vector2 offset(const mcoll::detail::MoveGridGroupId& id) const;
};

}}}  // namespace scn::step::map

#endif
