#ifndef SCN_STEP_BOSS_LOWPERWINDCTRL_H
#define SCN_STEP_BOSS_LOWPERWINDCTRL_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

}
class Component;
namespace boss {

// TODO: members.
class LowperWindCtrl {
public:
    LowperWindCtrl(Component& comp);
    ~LowperWindCtrl();
    void update();
    u32 set(const hel::math::Vector2& pos, f32 _2, f32 _3, f32 _4);
    void clear(u32 id);
    void clear();
    bool canSet(f32 x) const;
};

}}}  // namespace scn::step::boss

#endif
