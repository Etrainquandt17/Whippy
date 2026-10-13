#ifndef SCN_STEP_HERO_STORYMODEUTIL_H
#define SCN_STEP_HERO_STORYMODEUTIL_H

namespace scn {
namespace step {
class Component;
}
}

namespace scn {
namespace step {
namespace hero {

class StoryModeUtil {
public:
    static bool IsExtraMode(const Component& component);
};

}
}
}

#endif
