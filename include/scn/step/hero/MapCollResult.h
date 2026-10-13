#ifndef SCN_STEP_HERO_MAPCOLLRESULT_H
#define SCN_STEP_HERO_MAPCOLLRESULT_H

#include "hel/math/Vector2.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "scn/step/chara/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// The hero sources name chara::MapCollResult without its namespace.
typedef chara::MapCollResult MapCollResult;

// TODO: the two macros are left from a stand-in class: write result.groupFloor() and a copy of the id.
#define HERO_MAPCOLLRESULT_GROUP_FLOOR(result)                                                                         \
    (reinterpret_cast<const ::scn::step::chara::MapCollResult*>(                                                       \
         &static_cast<const ::scn::step::hero::MapCollResult&>(result))                                                \
         ->groupFloor())
// A copy of one of its group ids, which the original makes without a call.
#define HERO_MAPCOLLRESULT_GROUP(id) (::mcoll::detail::MoveGridGroupId(*reinterpret_cast<const u32*>(&(id))))

}}}  // namespace scn::step::hero

#endif
