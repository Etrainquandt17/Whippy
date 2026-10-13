#ifndef GOBJ_NODEREPOS_H
#define GOBJ_NODEREPOS_H

#include "g3d/NodeAccessor.h"
#include "types.h"

namespace gobj {

// TODO: size and members.
class NodeRepos {
public:
    g3d::NodeAccessor at(u32 index) const;
};

}

#endif
