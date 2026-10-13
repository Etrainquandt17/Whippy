#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_PLAYLISTCONTROLLER_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_PLAYLISTCONTROLLER_H

#include "g3d/NodeAccessor.h"
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
namespace enemy {

class PlayListController {
public:
    PlayListController(const char* name, common::effect::RequestorBuilder* builder, g3d::NodeAccessor node, common::view::ModelAccessor* model);
    ~PlayListController();

    void updateMain();
    void updateDebug();
    void resetPlayList(const char* name);
    void start();
    void end();
    void pause();
    void unpause();
    bool isPause() const;

private:
    u8 _0[0x390];
};

}
}
}
}

#endif
