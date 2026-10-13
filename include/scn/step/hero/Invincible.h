#ifndef SCN_STEP_HERO_INVINCIBLE_H
#define SCN_STEP_HERO_INVINCIBLE_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Invincible {
public:
    void set(u32 time);
    void setPermNoFlash();
    void setPerm();
    void unsetPerm();
    bool isMighty() const { return mIsMighty; }
    void clearMighty();
    void clear();

private:
    u32 _0[4];
    u8 _10;
    bool mIsMighty;
};

}}}  // namespace scn::step::hero

#endif
