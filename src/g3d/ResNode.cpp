#include "g3d/ResNode.h"

#include "hel/math/Vector3.h"

using hel::math::Vector3;

namespace g3d {

ResNode::ResNode() : nw4r::g3d::ResNode(0) {}

bool ResNode::isRoot() const {
    return id() == 0;
}

u32 ResNode::id() const {
    return GetID();
}

u32 ResNode::mtxId() const {
    return GetMtxID();
}

nw4r::g3d::ResNode ResNode::parent() const {
    return const_cast<ResNode*>(this)->GetParentNode();
}

nw4r::g3d::ResNode ResNode::child() const {
    return const_cast<ResNode*>(this)->GetChildNode();
}

Vector3 ResNode::translate() const {
    return Vector3(GetTranslate());
}

Vector3 ResNode::rotate() const {
    return Vector3(GetRotate());
}

Vector3 ResNode::scale() const {
    return Vector3(GetScale());
}

ResNode::ResNode(const nw4r::g3d::ResNode& node) : nw4r::g3d::ResNode(node) {}

}  // namespace g3d
