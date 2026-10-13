#ifndef SCN_ARENA_RENDERSET_H
#define SCN_ARENA_RENDERSET_H

#include "types.h"

namespace scn {
namespace arena {

class Camera;
class Component;

class RenderSet {
public:
    RenderSet(Component& component);
    ~RenderSet();

    Camera& camera();

private:
    u32 _0[0x97];
};

}
}

#endif
