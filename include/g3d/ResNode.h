#ifndef G3D_RESNODE_H
#define G3D_RESNODE_H

#include "nw4r/g3d/res/g3d_resnode.h"
#include "types.h"

namespace hel {
namespace math {
class Vector3;
}}  // namespace hel::math

namespace g3d {

class ResNode : public nw4r::g3d::ResNode {
public:
    ResNode();
    ResNode(const nw4r::g3d::ResNode& node);

    bool isValid() const;
    bool isRoot() const;
    u32 id() const;
    u32 mtxId() const;
    nw4r::g3d::ResNode parent() const;
    nw4r::g3d::ResNode child() const;
    hel::math::Vector3 translate() const;
    hel::math::Vector3 rotate() const;
    hel::math::Vector3 scale() const;
};

}  // namespace g3d

#endif
