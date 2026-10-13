#ifndef MCOLL_DETAIL_MOVEGRIDGROUP_H
#define MCOLL_DETAIL_MOVEGRIDGROUP_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: members and the other functions.
class MoveGridGroup {
public:
    hel::math::Vector2 getOffset();
    hel::math::Vector2 getDelta();
};

}
}

#endif
