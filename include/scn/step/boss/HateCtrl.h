#ifndef SCN_STEP_BOSS_HATECTRL_H
#define SCN_STEP_BOSS_HATECTRL_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

}
namespace boss {

class Boss;

// TODO: members.
class HateCtrl {
public:
    HateCtrl(Boss& boss);

    util::ObjRefHandle<hero::Hero> getMostHatedHero();

    void add(u32 player, u32 value);
    void sub(u32 player, u32 value);
    void subTop(u32 value);
    void clear();
    void clear(u32 player);
    void fix();
    void update();
    void shiftSearchTop();
};

}}}  // namespace scn::step::boss

#endif
