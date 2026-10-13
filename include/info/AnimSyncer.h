#ifndef INFO_ANIMSYNCER_H
#define INFO_ANIMSYNCER_H

#include "types.h"

namespace lyt {
class Layout;
}

namespace info {

// TODO: members.
class AnimSyncer {
public:
    void add(lyt::Layout& layout);
    void remove(lyt::Layout& layout);
    void update();
};

}

#endif
