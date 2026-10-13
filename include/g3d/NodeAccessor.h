#ifndef G3D_NODEACCESSOR_H
#define G3D_NODEACCESSOR_H

#include "types.h"

namespace hel {
namespace math {
class Vector3;
class Direction3;
class Matrix34;
}
}

namespace g3d {

class NodeLocalMtxAccessor;

class NodeAccessor {
public:
    NodeAccessor();
    NodeAccessor(const NodeAccessor& other);
    ~NodeAccessor();

    NodeAccessor& operator=(const NodeAccessor& other);

    hel::math::Vector3 worldTrans() const;
    hel::math::Direction3 worldRotate() const;
    hel::math::Vector3 worldScale() const;
    bool isVisible() const;
    void setVisibility(bool visible) const;
    void setVisibilityBelow(bool visible) const;
    NodeLocalMtxAccessor localMtx() const;
    hel::math::Matrix34 worldMtx() const;

private:
    u8 _0[0x14];
};

}

#endif
