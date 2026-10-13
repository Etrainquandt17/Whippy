#include "g3d/ResNode.h"

#include "hel/math/Vector3.h"

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

hel::math::Vector3 ResNode::translate() const {
    return hel::math::Vector3(GetTranslate());
}

hel::math::Vector3 ResNode::rotate() const {
    return hel::math::Vector3(GetRotate());
}

hel::math::Vector3 ResNode::scale() const {
    return hel::math::Vector3(GetScale());
}

ResNode::ResNode(const nw4r::g3d::ResNode& node) : nw4r::g3d::ResNode(node) {}

}  // namespace g3d
