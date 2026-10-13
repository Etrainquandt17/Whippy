#ifndef SCN_SUBGAME_COMMON_COLL_COLLISIONNODE_H
#define SCN_SUBGAME_COMMON_COLL_COLLISIONNODE_H

#include "g3d/CameraAccessor.h"
#include "hel/math/Vector2.h"
#include "nw4r/math/math_geometry.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace coll {

class CollisionNode {
public:
    class Result {
    public:
        static void ViewSegmentDPD(nw4r::math::SEGMENT3& segment, g3d::CameraAccessor camera, hel::math::Vector2 dpdPos);
        static void ViewSegment(nw4r::math::SEGMENT3& segment, g3d::CameraAccessor camera, f32 x, f32 y);
    };
};

}}}}  // namespace scn::subgame::common::coll

#endif
