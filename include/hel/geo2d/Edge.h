#ifndef HEL_GEO2D_EDGE_H
#define HEL_GEO2D_EDGE_H

#include "hel/math/Vector2.h"

namespace hel {
namespace math {
class Point2;
}

namespace geo2d {

// TODO: the other functions, and what the three vectors are. The users normalise the third as the edge's normal.
class Edge {
public:
    Edge(const hel::math::Point2& pos, const hel::math::Vector2&, const hel::math::Vector2&);

    hel::math::Vector2 _0;
    hel::math::Vector2 _8;
    hel::math::Vector2 _10;
};

}
}

#endif
