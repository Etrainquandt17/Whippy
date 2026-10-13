#ifndef OCOLL_NODEDESC_H
#define OCOLL_NODEDESC_H

#include "hel/math/Vector2.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace g3d {
class Model;
}

namespace ocoll {

class NodeDesc {
public:
    NodeDesc();
    ~NodeDesc();

    util::ObjRefHandle<g3d::Model> mModel;
    u32 _10;
    f32 _14;
    hel::math::Vector2 _18;
    hel::math::Vector2 _20;
    u8 _28;
};

}  // namespace ocoll

#endif
