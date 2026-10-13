#ifndef MCOLL_DETAIL_MOVEGRIDMANAGER_H
#define MCOLL_DETAIL_MOVEGRIDMANAGER_H

#include "mcoll/detail/MoveGridGroup.h"
#include "mcoll/detail/MoveGridGroupId.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: members and the other functions.
class MoveGridManager {
public:
    MoveGridGroup& moveGridGroup(const MoveGridGroupId& id);
};

}}  // namespace mcoll::detail

#endif
