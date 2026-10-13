#ifndef SCN_SUBGAME_GUNSHOOT_PARAM_DAMAGEANIMLIST_H
#define SCN_SUBGAME_GUNSHOOT_PARAM_DAMAGEANIMLIST_H

#include "param/ParamAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace param {

class DamageAnimList : public ::param::ParamAccessor {
public:
    struct Anim {
        u32 name[14];
        int playListIndex;
    };

    DamageAnimList(const char* name);

    Anim anim() const;

private:
    Anim mAnim;
};

}}}}  // namespace scn::subgame::gunshoot::param

#endif
