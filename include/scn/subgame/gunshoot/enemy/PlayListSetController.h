#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_PLAYLISTSETCONTROLLER_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_PLAYLISTSETCONTROLLER_H

#include "g3d/NodeAccessor.h"
#include "hel/common/NonCopyable.h"
#include "hel/common/ScopedPtr.h"
#include "types.h"

namespace scn {
namespace subgame {

namespace common {
namespace effect {
class RequestorBuilder;
}
namespace view {
class ModelAccessor;
}
}

namespace gunshoot {

namespace param {
class PlayListSet;
}

namespace enemy {

class PlayListController;

}
}
}
}

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

class PlayListSetController {
public:
    PlayListSetController(const param::PlayListSet& playListSet, common::effect::RequestorBuilder& builder, g3d::NodeAccessor node,
                          common::view::ModelAccessor& model);
    ~PlayListSetController();

    void initPlayListSet(common::effect::RequestorBuilder& builder, g3d::NodeAccessor node, common::view::ModelAccessor& model);
    void updateMain();
    void updateDebug();
    bool isValidIndex(int index) const;
    bool isStarting() const;
    void start(int index);
    void end();
    void endIfStarting();
    void pause();
    void unpause();
    bool isPause() const;

private:
    const param::PlayListSet& mPlayListSet;
    hel::common::ScopedPtr<PlayListController> mController;
    int mIndex;
};

}
}
}
}

#endif
