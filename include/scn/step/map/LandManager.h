#ifndef SCN_STEP_MAP_LANDMANAGER_H
#define SCN_STEP_MAP_LANDMANAGER_H

namespace mcoll {
class LandManager;
}

namespace scn {
namespace step {
namespace map {

class MoveGroupAccessor;

class LandManager {
public:
    mcoll::LandManager& native();
    const MoveGroupAccessor& mgAccessor() const;
};

}
}
}

#endif
