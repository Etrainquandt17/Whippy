#ifndef G3D_NODEACCESSOR_H
#define G3D_NODEACCESSOR_H

#include "types.h"
#ifdef G3D_NODEACCESSOR_IMPLICIT_ASSIGNMENT
#include "util/ObjRefHandle.h"
#endif

namespace hel {
namespace math {
class Vector3;
class Direction3;
class Matrix34;
}}  // namespace hel::math

namespace g3d {

class Model;
class NodeLocalMtxAccessor;

class NodeAccessor {
public:
    NodeAccessor();
    NodeAccessor(const NodeAccessor& other);
    // TODO: the destructor is the compiler's own in the original as well: every unit that destroys a node emits a
    // weak copy, and with util/ObjList.h included that copy brings the two LinkList.h strings into .data. A unit
    // that needs them defines G3D_NODEACCESSOR_IMPLICIT_DESTRUCTOR (with G3D_NODEACCESSOR_IMPLICIT_ASSIGNMENT).
#ifndef G3D_NODEACCESSOR_IMPLICIT_DESTRUCTOR
    ~NodeAccessor();
#endif

    // TODO: the assignment is the compiler's own in the original (an ObjRefHandle<Model> and a word). A unit
    // that expands it defines G3D_NODEACCESSOR_IMPLICIT_ASSIGNMENT ahead of its includes.
#ifndef G3D_NODEACCESSOR_IMPLICIT_ASSIGNMENT
    NodeAccessor& operator=(const NodeAccessor& other);
#endif

    hel::math::Vector3 worldTrans() const;
    hel::math::Direction3 worldRotate() const;
    hel::math::Vector3 worldScale() const;
    bool isVisible() const;
    void setVisibility(bool visible) const;
    void setVisibilityBelow(bool visible) const;
    NodeLocalMtxAccessor localMtx() const;
    hel::math::Matrix34 worldMtx() const;

private:
#ifdef G3D_NODEACCESSOR_IMPLICIT_ASSIGNMENT
    util::ObjRefHandle<Model> mModel;
    u32 _10;
#else
    u8 _0[0x14];
#endif
};

}  // namespace g3d

#endif
