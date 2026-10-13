#ifndef SCN_STEP_CHARA_INVINCIBLE_H
#define SCN_STEP_CHARA_INVINCIBLE_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

class Invincible {
public:
    Invincible();

    void update();
    bool isInvincible() const;
    void set(u32 frames);
    void clear();
    void setPerm();
    void unsetPerm();
    bool isPerm() const;
    void setMighty();
    void unsetMighty();
    bool isMighty() const;
    u32 getFrame() const;
    u32 getFlashAlpha() const;
    void updateFrame();

private:
    u32 mFrame;
    u32 mAnimFrame;
    bool mIsPerm;
    bool mIsMighty;
};

}}}  // namespace scn::step::chara

#endif
