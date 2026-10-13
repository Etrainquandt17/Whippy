#ifndef SCN_SUBGAME_GUNSHOOT_PARAM_PLAYLISTSET_H
#define SCN_SUBGAME_GUNSHOOT_PARAM_PLAYLISTSET_H

#include "param/ParamAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace param {

class PlayListSet : public ::param::ParamAccessor {
public:
    struct PlayListData {
        u32 name[32];
    };

    PlayListData playListData() const;
    const char* str(unsigned int reference) const;
};

}}}}  // namespace scn::subgame::gunshoot::param

#endif
